#include <cstdio>
#include <string>
#include<cuda_runtime.h>
#include<sys/time.h>
#include<vector>

using namespace std;

void print_data(float* arr, int width, int length, string flag) {
    int count=8;
    printf("%s :\n", flag.c_str());
    for (int i=0; i<count; i++) {
        for(int j=0; j<count; j++) {
            printf("%.3lf ", arr[i*length +i]);
        }
        printf("\n");
    }
}

float average(const vector<float> &timing) {
  double avg = 0;
  for(vector<float>::const_iterator it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  return avg;
}

void fillMat(float *mat, size_t rows, size_t cols)
{
    for(int row = 0; row < rows; ++row)
    {
        for(int col = 0; col < cols; ++col)
        {
            mat[row * cols + col] = col;
        }
    }
}


__global__ void matrixMulCUDA(float *C, float *A, float*B, int wA, int wB) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    float tmp = 0.0f;
    for (int i=0; i<wA; i++) {
        tmp += A[y * wA + i] * A[i * wB + x];
    }
    C[y * wB + x] = tmp;
}

template <int BLOCK_SIZE>
__global__ void matrixMulCUDA_share(float *C, float *A, float *B, int wA, int wB) {
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int aBegin = by * wA;
    int aEnd = aBegin + wA -1;
    int aStep = BLOCK_SIZE;
    int bBegin = bx * BLOCK_SIZE;
    int bStep = wB * BLOCK_SIZE;

    float cSub = 0;
    __shared__ float subA[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float subB[BLOCK_SIZE][BLOCK_SIZE];
    for (int a = aBegin, b = bBegin; a < aEnd; a+=aStep, b+=bStep) {
        subA[ty][tx] = A[a + ty * wA + tx];
        subB[ty][tx] = B[b + ty * wB + tx];
        __syncthreads();
        for (int i=0; i<BLOCK_SIZE; i++) {
            cSub += subA[ty][i] * subB[i][tx];
        }
        __syncthreads();
    }
    C[((by*BLOCK_SIZE+ty)*wB + bx*BLOCK_SIZE+tx)] = cSub;
}

template<int WIDTH>
void testMatrixMul()
{
    size_t mem_size = sizeof(float) * WIDTH * WIDTH;
    float *mat1 = (float *)malloc(mem_size);
    float *mat2 = (float *)malloc(mem_size);
    float *mat3 = (float *)malloc(mem_size);
    // initialize mat1 and mat2
    fillMat(mat1, WIDTH, WIDTH);
    fillMat(mat2, WIDTH, WIDTH);

    // matrixMul<WIDTH>(mat3, mat1, mat2);

    float* d_mat1, *d_mat2, *d_mat3;
    cudaError_t error;
    error = cudaMalloc((void**)&d_mat1, mem_size);
    error = cudaMemcpy(d_mat1, mat1, mem_size, cudaMemcpyHostToDevice);
    if (error != cudaSuccess) {
        printf("cudaMemcpy d_mat1 returned error %s (code %d), line(%d)\n", cudaGetErrorString(error), error, __LINE__);
        exit(1);
    }
    error = cudaMalloc((void**)&d_mat2, mem_size);
    error = cudaMemcpy(d_mat2, mat2, mem_size, cudaMemcpyHostToDevice);
    if (error != cudaSuccess) {
        printf("cudaMemcpy d_mat2 returned error %s (code %d), line(%d)\n", cudaGetErrorString(error), error, __LINE__);
        exit(1);
    }
    error = cudaMalloc((void**)&d_mat3, mem_size);

    int block_size = 32;
    dim3 threads(block_size, block_size);
    dim3 grid(WIDTH/threads.x, WIDTH/threads.y);
    // Allocate CUDA events that we'll use for timing
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, NULL);

    vector<float> times;
    int loops = 3;
    for (int i=0;i<loops; i++) {
        cudaEventRecord(start, NULL);
        matrixMulCUDA<<<grid, threads>>>(d_mat3, d_mat1, d_mat2, WIDTH, WIDTH);
        // if (block_size ==16) {
        //     matrixMulCUDA_share<16><<<grid, threads>>>(d_mat3, d_mat1, d_mat2, WIDTH, WIDTH);
        // }
        // else{
        //     matrixMulCUDA_share<32><<<grid, threads>>>(d_mat3, d_mat1, d_mat2, WIDTH, WIDTH);
        // }
        
        cudaEventRecord(stop, NULL);
        cudaEventSynchronize(stop);
        float time = 0;
        cudaEventElapsedTime(&time, start, stop);
        times.push_back(time);
    }
    float avg_time = average(times);
    printf("cuda %d time: %lf ms\n", WIDTH, avg_time);
    

    // cudaEventRecord(stop, NULL);
    // cudaEventSynchronize(stop);
    // float time = 0;
    // cudaEventElapsedTime(&time, start, stop);
    // printf("run time:%.lf ms\n", time/loops);

    error = cudaMemcpy(mat3, d_mat3, mem_size, cudaMemcpyDeviceToHost);

    print_data(mat1, WIDTH, WIDTH, "mat1");
    print_data(mat2, WIDTH, WIDTH, "mat2");
    print_data(mat3, WIDTH, WIDTH, "mat3");

    free(mat1);
    free(mat2);
    free(mat3);
    cudaFree(d_mat1);
    cudaFree(d_mat2);
    cudaFree(d_mat3);
}

int main(int argc, char const *argv[])
{
    // testMatrixMul<256 >();
    // testMatrixMul<512 >();
    // testMatrixMul<768 >();
    testMatrixMul<2048>();
    // testMatrixMul<1280>();
    // testMatrixMul<1536>();
    // testMatrixMul<1792>();
    // testMatrixMul<2048>();
    return 0;
}
