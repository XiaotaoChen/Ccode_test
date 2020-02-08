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
__global__ void reduce_kernel1(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx>=len_a) return;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = A[idx];
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
__global__ void reduce_kernel2(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx>=len_a) return;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = A[idx];
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
__global__ void reduce_kernel3(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx>=len_a) return;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    sA[tid] = A[idx];
    __syncthreads();
    for (int s=blockDim.x/2; s>0; s>>=1) {
        if(tid <s) {
            if (tid+s < blockDim.x) sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

// first add during load
__global__ void reduce_kernel4(int*A, int*out, int len_a) {
    int idx = blockDim.x * (blockIdx.x * 2) + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ int sA[];
    if (idx + blockDim.x < len_a) {
        sA[tid] = A[idx] + A[blockDim.x + idx];
    }
    else{
        sA[tid] = A[idx];
    }
    
    __syncthreads();
    for (int s=blockDim.x/2; s>0; s>>=1) {
        if(tid <s) {
            if (tid+s < blockDim.x) sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    if (tid==0) out[bid] = sA[0];
}

__global__ void copy(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx >= len_a) return;
    out[idx] = A[idx];
}

int reduce(int*A, int len_a, int numThreads){
    // numBlocks = (len_a + numThreads) / numThreads;
    int numBlocks = (len_a + numThreads*2 -1) / numThreads/2;
    int*tmp;
    cudaMalloc((void**)&tmp, numBlocks*sizeof(int));
    while(len_a>1) {
        printf("len:%d, numBlocks:%d, numThreads:%d\n", len_a, numBlocks, numThreads);
        // reduce_kernel1<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // reduce_kernel2<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // reduce_kernel3<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        // len_a = numBlocks;
        // numBlocks = (numBlocks+numThreads-1)/numThreads;

        reduce_kernel4<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(A, tmp, len_a);
        len_a = numBlocks;
        numBlocks = (len_a + numThreads*2 -1) / numThreads/2;
        copy<<<numBlocks, numThreads>>>(tmp, A, len_a);
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
    int numBlocks = (len_a + numThreads - 1) / numThreads;

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

        int result = reduce(d_A, len_a, numThreads);
        printf("result:%d\n", result);

        cudaEventRecord(end, NULL);
        cudaEventSynchronize(end);
        float time = 0;
        cudaEventElapsedTime(&time, start, end);
        times.push_back(time);
    }
    printf("reduce avg time:%lf\n", average(times));

}