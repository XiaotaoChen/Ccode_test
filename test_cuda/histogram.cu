#include<cstdio>
#include<vector>
#include<string>
#include<cuda_runtime.h>
#include<thrust/fill.h>


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

void assign_value(int *data, int len) {
    for (int i=0; i<len; i++) data[i] = i % 256;
}

__global__ void naive_kernel(int *data, int *out, int len) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    atomicAdd(&(out[data[tid]]), 1);
}

__global__ void histogram_kernel(int *data, int *out, int len) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int thx = threadIdx.x;
    extern __shared__ int sdata[];
    sdata[thx] = 0;
    __syncthreads();

    if (tid<len) atomicAdd(&(sdata[data[tid]]), 1);
    __syncthreads();

    atomicAdd(&(out[thx]), sdata[thx]);
}

__global__ void histogram_kernel_multiple_read(int *data, int *out, int len, int stride) {
    int tid = blockIdx.x * (blockDim.x * stride) + threadIdx.x;
    int thx = threadIdx.x;
    extern __shared__ int sdata[];
    sdata[thx] = 0;
    __syncthreads();
    int end = min(tid + blockDim.x * stride, len);
    for (int i=tid; i< end; i+=blockDim.x) {
        atomicAdd(&(sdata[data[i]]), 1);
    }
    __syncthreads();

    atomicAdd(&(out[thx]), sdata[thx]);
}

void cal_histogram(int *data, int *out, int len, int numThreads) {
    int stride = 32;
    int numblocks = (len + (numThreads*stride) -1) / (numThreads * stride);
    // naive_kernel<<<numblocks, numThreads>>>(data, out, len);
    // histogram_kernel<<<numblocks, numThreads, 256 * sizeof(int)>>>(data, out, len);
    histogram_kernel_multiple_read<<<numblocks, numThreads, 256 * sizeof(int)>>>(data, out, len, stride);
}

void cal_histogram_cpu(int *data, int *out, int len) {
    for (int i=0; i<len; i++) out[data[i]]++;
}

int main() {
    int numThreads = BLOCK_SIZE;
    int len = 512 * 1024 * 1024;
    int *h_data = (int*)malloc(len * sizeof(int));
    assign_value(h_data, len);

    int *d_data;
    cudaMalloc((void**)&d_data, len * sizeof(int));
    cudaMemcpy(d_data, h_data, len * sizeof(int), cudaMemcpyHostToDevice);

    int *result = (int*) malloc(256 * sizeof(int));
    fill_n(result, 256, 0);
    cal_histogram_cpu(h_data, result, len);
    print_info(result, 256, "cpu result");

    int *d_result;
    cudaMalloc((void**)&d_result, 256 * sizeof(int));
    // thrust::fill(d_result, d_result + 256, 0);
    fill_n(result, 256, 0);
    cudaMemcpy(d_result, result, 256 * sizeof(int), cudaMemcpyHostToDevice);

    vector<float> times;
    int loops = 1;
    for (int i=0; i<loops; i++) {
        cudaEvent_t start, end;
        cudaEventCreate(&start);
        cudaEventCreate(&end);
        cudaEventRecord(start, NULL);

        cal_histogram(d_data, d_result, len, numThreads);
        
        cudaEventRecord(end, NULL);
        cudaEventSynchronize(end);
        float time = 0;
        cudaEventElapsedTime(&time, start, end);
        times.push_back(time);
    }
    printf("cal histogram avg time:%lf\n", average(times));

    cudaMemcpy(result, d_result, 256 * sizeof(int), cudaMemcpyDeviceToHost);
    print_info(result, 256, "gpu result");

    cudaFree(d_data);
    cudaFree(d_result);
    free(h_data);
    free(result);
}