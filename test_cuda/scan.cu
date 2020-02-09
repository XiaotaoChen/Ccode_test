#include<cstdio>
#include<vector>
#include<string>
#include<cuda_runtime.h>
// #include <thrust/sequence.h>
#include <thrust/scan.h>
#include <thrust/execution_policy.h> // thrust::host/device

#define BLOCK_SIZE 32

using namespace std;

float average(const vector<float> &timing) {
  double avg = 0;
  for(vector<float>::const_iterator it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

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

__global__ void exclusive_scan(int *A, int N) {
    int thx = blockDim.x * blockIdx.x + threadIdx.x;
    if (thx >= N) return;
    __shared__ int logN;
    if (thx == 0) {
        logN = log2f(N);
    }
    __syncthreads();
    for (int i=0; i<logN; i++) {
        int d2 = powf(2, i+1);
        int dd2 = d2/2;
        if (thx%d2==d2-1) {
            A[thx] += A[thx - dd2];
        }
        __syncthreads();
    }
    if (thx == 0) {
        A[N-1] = 0;
    }
    __syncthreads();
    for (int i=logN-1; i>=0; i--) {
        int d2 = powf(2, i+1);
        int dd2 = d2/2;
        if (thx%d2==d2-1) {
            int tmp = A[thx-dd2];
            // A[thx-dd2] = tmp;
            A[thx-dd2] = A[thx];
            A[thx] += tmp;
        }
        __syncthreads();
    }
}

int main() {
    int len_a = BLOCK_SIZE;
    int numThreads = BLOCK_SIZE;
    int numBlocks = (len_a + numThreads - 1) / numThreads;

    int* A = (int*) malloc(len_a * sizeof(int));
    int* th_h_A = (int*) malloc(len_a * sizeof(int));
    // file a,b
    for (int i=0; i<len_a; i++) A[i] = i;
    for (int i=0; i<len_a; i++) th_h_A[i] = i;
    print_info(A, len_a, "A");

    int *d_A, *th_A;
    cudaMalloc((void**)&d_A, len_a * sizeof(int));
    cudaMalloc((void**)&th_A, len_a * sizeof(int));

    cudaMemcpy(d_A, A, len_a * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(th_A, A, len_a * sizeof(int), cudaMemcpyHostToDevice);

    // thrust scan
    thrust::exclusive_scan(thrust::device, th_A, th_A+len_a, th_A, 0);
    cudaMemcpy(th_h_A, th_A, len_a * sizeof(int), cudaMemcpyDeviceToHost);
    // thrust::exclusive_scan(thrust::host, th_h_A, th_h_A+len_a, th_h_A, 0);

    print_info(th_h_A, len_a, "th_h_A");

    vector<float> times;
    int loops = 1;
    for (int i=0; i<loops; i++) {
        cudaEvent_t start, end;
        cudaEventCreate(&start);
        cudaEventCreate(&end);
        cudaEventRecord(start, NULL);

        exclusive_scan<<<numBlocks, numThreads>>>(d_A, len_a);

        cudaEventRecord(end, NULL);
        cudaEventSynchronize(end);
        float time = 0;
        cudaEventElapsedTime(&time, start, end);
        times.push_back(time);
    }
    printf("exclusive scan avg time:%lf\n", average(times));
    
    cudaMemcpy(A, d_A, len_a * sizeof(float), cudaMemcpyDeviceToHost);
    print_info(A, len_a, "A");

}