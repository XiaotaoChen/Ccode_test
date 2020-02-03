#include <iostream>
#include<cuda_runtime.h>

using namespace std;

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
        tmp += A[x * wA + i] * A[i * wB + y];
    }
    C[x * wB + y] = tmp;
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
    error = cudaMalloc((void**)d_mat1, mem_size);
    error = codaMemcpy(d_mat1, mat1, mem_size, cudaMemcpyHostToDevice);
    if (error != cudaSuccess) {
        printf("cudaMemcpy d_mat1 returned error %s (code %d), line(%d)\n", cudaGetErrorString(error), error, __LINE__);
        exit(1);
    }
    error = cudaMalloc((void**)d_mat2, mem_size);
    error = codaMemcpy(d_mat2, mat2, mem_size, cudaMemcpyHostToDevice);
    if (error != cudaSuccess) {
        printf("cudaMemcpy d_mat2 returned error %s (code %d), line(%d)\n", cudaGetErrorString(error), error, __LINE__);
        exit(1);
    }
    error = cudaMalloc((void**)d_mat3, mem_size);
    error = codaMemcpy(d_mat3, mat3, mem_size, cudaMemcpyHostToDevice);
    if (error != cudaSuccess) {
        printf("cudaMemcpy d_mat3 returned error %s (code %d), line(%d)\n", cudaGetErrorString(error), error, __LINE__);
        exit(1);
    }

    int block_size = 32;
    dim3 threads(block_size, block_size);
    dim3 grid(WIDTH/threads.x, WIDTH/threads.y);
    matrixMulCUDA<<<grid, threads>>>(d_mat3, d_mat1, d_mat2, WIDTH, WIDTH);

    free(mat1);
    free(mat2);
    free(mat3);
}

int main(int argc, char const *argv[])
{
    // testMatrixMul<256 >();
    // testMatrixMul<512 >();
    // testMatrixMul<768 >();
    testMatrixMul<1024>();
    // testMatrixMul<1280>();
    // testMatrixMul<1536>();
    // testMatrixMul<1792>();
    // testMatrixMul<2048>();
    return 0;
}