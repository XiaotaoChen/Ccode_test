#include<cstdio>
#include<cuda_runtime.h>
#include<vector>
#include<string>

#define BLOCK_SIZE 1024

using namespace std;

float average(const vector<float> &timing) {
  double avg = 0;
  for(vector<float>::const_iterator it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

  return avg;
}

void print_info(float *data, int len, string flag) {
    printf("%s frist ten:\n", flag.c_str());
    for (int i=0; i<10; i++){
        printf("%.4lf ", data[i]);
    }
    printf("\n");
    printf("%s last ten:\n", flag.c_str());
    for (int i=len -10; i<len; i++){
        printf("%.4lf ", data[i]);
    }
    printf("\n");
}

__global__ void convDirect(float *A, float*B, float*C, int len_a, int len_b, int len_c) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid > len_c) return;
    float sum =0.0f;
    for (int i=0; i<len_b; i++) {
        int idx = tid - i;
        if (idx >=0 && idx < len_a) {
            sum += A[idx] * B[i];
        }
    }
    C[tid] = sum;
}

__global__ void conv_shared_memory(float *A, float *B, float *C, int len_a, int len_b, int len_c) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid > len_c) return;
    int tx = threadIdx.x;
    extern __shared__ float sA[];
    if (tid < len_a) {
        sA[tx] = A[tid];
    }
    __syncthreads();
    float sum = 0.0f;
    for (int i=0; i<len_b; i++) {
        int idx = tid - i;
        int sx = tx - i;
        if (tid < len_a && sx>=0) {
            sum += sA[sx] * B[i];
        }
        else if (idx >=0 && idx < len_a) {
            sum += A[idx] * B[i];
        }
    }
    __syncthreads();
    C[tid] = sum;
}

__constant__ static float c_B[1024];
__global__ void conv_shared_const_memory(float *A, float*B, float *C, int len_a, int len_b, int len_c) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int tx = threadIdx.x;
    if (tid > len_c) return;
    extern __shared__ float sA[];
    if (tid < len_a) {
        sA[tx] = A[tid];
    }
    __syncthreads();
    float sum = 0.0f;
    for (int i=0; i<len_b; i++) {
        int idx = tid - i;
        int sx = tx - i;
        if (tid < len_a && sx >= 0) {
            sum += sA[sx] * c_B[i];
        }
        else if (idx >= 0 && idx < len_a) {
            sum += A[idx] *c_B[i];
        }
    }
    __syncthreads();
    C[tid] = sum;
}

int main() {
    int len_a = 1024 * 1024 * 256;
    int len_b = 1000;
    int len_c = len_a + len_b - 1;
    int numThreads = BLOCK_SIZE;
    int numBlocks = (len_c + numThreads - 1) / numThreads;

    float* A = (float*) malloc(len_a * sizeof(float));
    float* B = (float*) malloc(len_b * sizeof(float));
    float* C = (float*) malloc(len_c * sizeof(float));
    // file a,b
    for (int i=0; i<len_a; i++) A[i] = i;
    for (int i=0; i<len_b; i++) B[i] = i;
    // print_info(A, "A");
    // print_info(B, "B");

    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, len_a * sizeof(float));
    cudaMalloc((void**)&d_B, len_b * sizeof(float));
    cudaMalloc((void**)&d_C, len_c * sizeof(float));

    cudaMemcpy(d_A, A, len_a * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, len_b * sizeof(float), cudaMemcpyHostToDevice);

    vector<float> times;
    int loops = 3;
    for (int i=0; i<loops; i++) {
        cudaEvent_t start, end;
        cudaEventCreate(&start);
        cudaEventCreate(&end);
        cudaEventRecord(start, NULL);

        convDirect<<<numBlocks, numThreads>>>(d_A, d_B, d_C, len_a, len_b, len_c);

        // conv_shared_memory<<<numBlocks, numThreads, numThreads * sizeof(float)>>>(d_A, d_B, d_C, len_a, len_b, len_c);

        // cudaMemcpyToSymbol(c_B, d_B, len_b * sizeof(float));
        // conv_shared_memory<<<numBlocks, numThreads, numThreads * sizeof(float)>>>(d_A, d_B, d_C, len_a, len_b, len_c);

        cudaEventRecord(end, NULL);
        cudaEventSynchronize(end);
        float time = 0;
        cudaEventElapsedTime(&time, start, end);
        times.push_back(time);
    }
    printf("convDirect avg time:%lf\n", average(times));
    
    cudaMemcpy(C, d_C, len_c * sizeof(float), cudaMemcpyDeviceToHost);
    print_info(C, len_c, "C");

}