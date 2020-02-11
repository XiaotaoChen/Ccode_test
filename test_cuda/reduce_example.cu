#include <cstdio>
#include <vector>
#include <cuda_runtime.h>

// unroll the last warp
__device__ void warpFunc(volatile int* sA, int tid) {
    sA[tid] += sA[tid+32];
    sA[tid] += sA[tid+16];
    sA[tid] += sA[tid+8];
    sA[tid] += sA[tid+4];
    sA[tid] += sA[tid+2];
    sA[tid] += sA[tid+1];
}

__global__ void reduce_kernel3(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ volatile int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
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

__global__ void reduce_kernel3_2(int*A, int*out, int len_a) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int bid = blockIdx.x;
    int tid = threadIdx.x;
    extern __shared__ volatile int sA[];
    sA[tid] = 0;
    if (idx < len_a) sA[tid] = A[idx];
    __syncthreads();
    for (int s=blockDim.x/2; s>32; s>>=1) {
        if(tid <s) {
          sA[tid] += sA[tid+s];
        }
        __syncthreads();
    }
    // only sA is volatile can do this
    if (tid<32) {
        sA[tid] += sA[tid+32];
        sA[tid] += sA[tid+16];
        sA[tid] += sA[tid+8];
        sA[tid] += sA[tid+4];
        sA[tid] += sA[tid+2];
        sA[tid] += sA[tid+1];
    }
    if (tid==0) out[bid] = sA[0];
}


int sum_on_cpu(int *data, int len) {
    int result = 0;
    for (int i=0; i<len; i++) result += data[i];
    return result;
}

int sum_on_gpu(int *data, int len, int numThreads, int flag) {
    int numBlocks = (len + numThreads -1) / numThreads;
    int*tmp;
    cudaMalloc((void**)&tmp, numBlocks*sizeof(int));
    while(len>1) {
        if (flag==0) {
            reduce_kernel3<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(data, tmp, len);
        }
        else if (flag==1){
            reduce_kernel3_2<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(data, tmp, len);
        }
        else{
            reduce_kernel3_3<<<numBlocks, numThreads, numThreads*sizeof(int)>>>(data, tmp, len);
        }
        
        len = numBlocks;
        numBlocks = (numBlocks+numThreads-1)/numThreads;
        cudaMemcpy(data, tmp, sizeof(int) * len, cudaMemcpyDeviceToDevice);
    }
    int result;
    cudaMemcpy(&result, tmp, sizeof(int), cudaMemcpyDeviceToHost);
    return result;
}

int main() {
    int len = 1024 * 1024;
    int numThreads = 256;
    int *h_data = (int*) malloc(len * sizeof(int));
    std::fill_n(h_data, len, 1);

    int* d_data1, *d_data2, *d_data3;
    cudaMalloc((void**)&d_data1, len * sizeof(int));
    cudaMemcpy(d_data1, h_data, len*sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void**)&d_data2, len * sizeof(int));
    cudaMemcpy(d_data2, h_data, len*sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void**)&d_data3, len * sizeof(int));
    cudaMemcpy(d_data3, h_data, len*sizeof(int), cudaMemcpyHostToDevice);
    
    int cpu_result = sum_on_cpu(h_data, len);
    int gpu_result1 = sum_on_gpu(d_data1, len, numThreads, 0);
    int gpu_result2 = sum_on_gpu(d_data2, len, numThreads, 1);
    int gpu_result3 = sum_on_gpu(d_data3, len, numThreads, 2);
    printf("result: cpu:%d, gpu k1:%d, k2:%d, k3:%d\n", cpu_result, gpu_result1, gpu_result2, gpu_result3);

    cudaFree(d_data1);
    cudaFree(d_data2);
    cudaFree(d_data3);
    free(h_data);

}