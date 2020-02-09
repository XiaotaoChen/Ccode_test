#include<cstdio>
#include<vector>
#include<string>
#include<cuda_runtime.h>
// #include <thrust/sequence.h>
#include <thrust/reduce.h>
#include <thrust/execution_policy.h> // thrust::host/device

#define BLOCK_SIZE 256

using namespace std;

float average(const vector<float> &timing) {
  double avg = 0;
  for(vector<float>::const_iterator it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  return avg;
}

void print_info(int *data, int len, string flag) {
    printf("%s frist ten:\n", flag.c_str());
    for (int i=0; i<10; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("%s last ten:\n", flag.c_str());
    for (int i=len -10; i<len; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}

void print_device_info(int *device_data, int len, string flag) {
    int*data = (int*)malloc(len * sizeof(int));
    cudaMemcpy(data, device_data, len*sizeof(int), cudaMemcpyDeviceToHost);

    printf("%s frist ten:\n", flag.c_str());
    for (int i=0; i<10 && i < len; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    if (len>10) {
        printf("%s last ten:\n", flag.c_str());
        for (int i=len -10; i<len; i++){
            printf("%d ", data[i]);
        }
        printf("\n");
    }
}

// interleved addressing, divergent warps branch
// time: 33.3 ms
__global__ void reduce_kernel1(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    __syncthreads();
    for (int s=1; s<blockDim.x; s*=2) {
        if(tid%(2*s)== 0) {
            if (tid+s < len_a) sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

// inerleved addressing, bands conflict
// time: 20 ms
__global__ void reduce_kernel2(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    __syncthreads();
    for (int s=1; s<blockDim.x; s*=2) {
        int run_id = 2 * s * tid;
        if(run_id <blockDim.x) {
            if (run_id+s < blockDim.x) sA[run_id] += sA[run_id+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

// sequential addressing
// time: 17.9 ms
__global__ void reduce_kernel3(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    __syncthreads();
    for (int s=blockDim.x/2; s>0; s>>=1) {
        if(tid <s) {
          sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

// first add during load
// time:10.78 ms
__global__ void reduce_kernel4(int*A, int*out, int len_a) {
    int idx = blockDim.x * (blockIdx.x * 2) + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    if (idx + blockDim.x < len_a) sA[tid] += A[idx + blockDim.x];
    
    __syncthreads();
    for (int s=blockDim.x/2; s>0; s>>=1) {
        if(tid <s) {
            sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

// unroll the last warp
__device__ void warpFunc(volatile int* sdata, int tid) {
    sdata[tid] += sdata[tid+32];
    sdata[tid] += sdata[tid+16];
    sdata[tid] += sdata[tid+8];
    sdata[tid] += sdata[tid+4];
    sdata[tid] += sdata[tid+2];
    sdata[tid] += sdata[tid+1];
}
// time: 8.0 ms
__global__ void reduce_kernel5(int *A, int *out, int len_a) {
    int idx = blockDim.x * (blockIdx.x * 2) + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    if (idx + blockDim.x < len_a) sA[tid] += A[idx + blockDim.x];
    
    __syncthreads();
    for (int s=blockDim.x/2; s>32; s>>=1) {
        if(tid <s) {
            sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid<32) warpFunc(sA, tid);
    if (tid==0) out[bid] = sA[0];
}

// completely unroll
// time: 8.03 ms
__global__ void reduce_kernel6(int *A, int *out, int len_a) {
    int idx = blockDim.x * (blockIdx.x * 2) + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    if (idx + blockDim.x < len_a) sA[tid] += A[idx + blockDim.x];
    __syncthreads();

    if (blockDim.x >= 1024) { if (tid < 512) sA[tid] += sA[tid+512]; __syncthreads();}
    if (blockDim.x >= 512) { if (tid < 256) sA[tid] += sA[tid+256]; __syncthreads();}
    if (blockDim.x >= 256) { if (tid < 128) sA[tid] += sA[tid+128]; __syncthreads();}
    if (blockDim.x >= 128) { if (tid < 64) sA[tid] += sA[tid+64]; __syncthreads();}
    if (tid<32) warpFunc(sA, tid);
    // if (tid<32) {
    //     sA[tid]+= sA[tid+32];
    //     sA[tid]+= sA[tid+16];
    //     sA[tid]+= sA[tid+8];
    //     sA[tid]+= sA[tid+4];
    //     sA[tid]+= sA[tid+2];
    //     sA[tid]+= sA[tid+1];
    // }
    if (tid==0) out[bid] = sA[0];
}

template <unsigned int blockSize>
__device__ void warpReduce(volatile int *sdata, int tid) {
    if (blockSize >=64) sdata[tid] += sdata[tid+32];
    if (blockSize >=32) sdata[tid] += sdata[tid+16];
    if (blockSize >=16) sdata[tid] += sdata[tid+8];
    if (blockSize >=8) sdata[tid] += sdata[tid+4];
    if (blockSize >=4) sdata[tid] += sdata[tid+2];
    if (blockSize >=2) sdata[tid] += sdata[tid+1];
}

// load as much as data
__global__ void reduce_kernel7(int *A, int *out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    int griz = gridDim.x * blockDim.x;
    extern __shared__ int sA[];
    sA[tid] = 0;
    int tmp_id = idx;
    while(tmp_id <len_a) {
        if (tmp_id < len_a) sA[tid] = A[tmp_id];
        tmp_id += griz;
    }
    __syncthreads();
    if (blockDim.x >= 1024) { if (tid < 512) sA[tid] += sA[tid+512]; __syncthreads();}
    if (blockDim.x >= 512) { if (tid < 256) sA[tid] += sA[tid+256]; __syncthreads();}
    if (blockDim.x >= 256) { if (tid < 128) sA[tid] += sA[tid+128]; __syncthreads();}
    if (blockDim.x >= 128) { if (tid < 64) sA[tid] += sA[tid+64]; __syncthreads();}
    if (tid<32) warpFunc(sA, tid);
    if (tid==0) out[bid] = sA[0];
}


int reduce(int*A, int len_a, int numThreads){
    int numBlocks = (len_a + numThreads) / numThreads;
    // int numBlocks = (len_a + numThreads*2 -1) / numThreads/2;
    int*tmp;
    cudaMalloc((void**)&tmp, numBlocks*sizeof(int));
    while(len_a>1) {
        printf("len:%d, numBlocks:%d, numThreads:%d\n", len_a, numBlocks, numThreads);
        // reduce_kernel1<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // // time: 33.3 ms

        // reduce_kernel2<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // // time: 20 ms

        reduce_kernel3<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // time: 17.9 ms
        
        len_a = numBlocks;
        numBlocks = (numBlocks+numThreads-1)/numThreads;
        cudaMemcpy(A, tmp, sizeof(int) * len_a, cudaMemcpyDeviceToDevice);
        // print_device_info(tmp, len_a, "tmp");
    }
    int result;
    cudaMemcpy(&result, tmp, sizeof(int), cudaMemcpyDeviceToHost);
    return result;
}

int reduce_2(int*A, int len_a, int numThreads){
    int numBlocks = (len_a + numThreads*2 -1) / numThreads/2;
    int*tmp;
    cudaMalloc((void**)&tmp, numBlocks*sizeof(int));
    while(len_a>1) {
        printf("len:%d, numBlocks:%d, numThreads:%d\n", len_a, numBlocks, numThreads);
        
        // reduce_kernel4<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // // time:10.78 ms

        // reduce_kernel5<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // // time: 8.0 ms

        reduce_kernel6<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // time: 8.03 ms

        len_a = numBlocks;
        numBlocks = (numBlocks+numThreads*2-1)/numThreads/2;
        cudaMemcpy(A, tmp, sizeof(int) * len_a, cudaMemcpyDeviceToDevice);
        // print_device_info(tmp, len_a, "tmp");
    }
    int result;
    cudaMemcpy(&result, tmp, sizeof(int), cudaMemcpyDeviceToHost);
    return result;
}

int reduce_3(int*A, int len_a, int numThreads){
    // int count_per_threads = 2;
    // int count_per_blocks = 2;
    int numBlocks = (len_a + numThreads*8 -1) / numThreads/8;
    int*tmp;
    cudaMalloc((void**)&tmp, numBlocks*sizeof(int));
    while(len_a>1) {
        printf("len:%d, numBlocks:%d, numThreads:%d\n", len_a, numBlocks, numThreads);
        reduce_kernel7<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // time:  ms

        len_a = numBlocks;
        numBlocks = (numBlocks+numThreads*8-1)/numThreads/8;
        cudaMemcpy(A, tmp, sizeof(int) * len_a, cudaMemcpyDeviceToDevice);
        // print_device_info(tmp, len_a, "tmp");
    }
    int result;
    cudaMemcpy(&result, tmp, sizeof(int), cudaMemcpyDeviceToHost);
    return result;
}


int main() {
    // int len_a = 256 * 256 * 256;
    int len_a = 1024*1024*1024;
    int numThreads = BLOCK_SIZE;

    int* A = (int*) malloc(len_a * sizeof(int));
    int* th_h_A = (int*) malloc(len_a * sizeof(int));
    // file a,b
    for (int i=0; i<len_a; i++) A[i] = 1;
    for (int i=0; i<len_a; i++) th_h_A[i] = 1;
    // print_info(A, len_a, "A");

    int *d_A, *th_A;
    cudaMalloc((void**)&d_A, len_a * sizeof(int));
    cudaMalloc((void**)&th_A, len_a * sizeof(int));

    cudaMemcpy(d_A, A, len_a * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(th_A, A, len_a * sizeof(int), cudaMemcpyHostToDevice);

    int th_result;
    // thrust reduce
    th_result = thrust::reduce(thrust::device, th_A, th_A+len_a, 0);
    // th_result = thrust::reduce(thrust::host, th_h_A, th_h_A+len_a, 0);
    printf("th result:%d\n", th_result);

    vector<float> times;
    int loops = 1;
    for (int i=0; i<loops; i++) {
        cudaEvent_t start, end;
        cudaEventCreate(&start);
        cudaEventCreate(&end);
        cudaEventRecord(start, NULL);

        // int result = reduce(d_A, len_a, numThreads);
        int result = reduce_2(d_A, len_a, numThreads);
        printf("result:%d\n", result);

        cudaEventRecord(end, NULL);
        cudaEventSynchronize(end);
        float time = 0;
        cudaEventElapsedTime(&time, start, end);
        times.push_back(time);
    }
    printf("reduce avg time:%lf\n", average(times));

    free(A);
    free(th_h_A);
    cudaFree(d_A);
    cudaFree(th_A);

}