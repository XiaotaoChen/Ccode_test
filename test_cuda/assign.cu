#include <stdio.h>

__global__
void revert(int n, float* a, float *b) {
    *b = - (*a);
}

int main() {
    float* a, *b, *a_d, *b_d;
    a = (float*)malloc(sizeof(float));
    b = (float*)malloc(sizeof(float));
    *a = 5.0f;
    *b = 0;
    cudaMalloc((void**)&a_d, sizeof(float));
    cudaMalloc((void**)&b_d, sizeof(float));
    cudaMemcpy(a_d, a, sizeof(float), cudaMemcpyHostToDevice);
    // *b_d = *a_d;
    int N = 1;
    revert<<<(N+255)/256, 256>>>(N, a_d, b_d);
    cudaMemcpy(b, b_d, sizeof(float), cudaMemcpyDeviceToHost);

    // *a = -(*a);
    // cudaMemcpy(b_d, a, sizeof(float), cudaMemcpyHostToDevice);
    // cudaMemcpy(b, b_d, sizeof(float), cudaMemcpyDeviceToHost);

    
    printf("a:%.2f, b:%.2f\n", *a, *b);
    return 0;
}


// __global__
// void saxpy(int n, float a, float *x, float *y)
// {
//   int i = blockIdx.x*blockDim.x + threadIdx.x;
//   if (i < n) y[i] = a*x[i] + y[i];
// }

// int main(void)
// {
//   int N = 1<<20;
//   float *x, *y, *d_x, *d_y;
//   x = (float*)malloc(N*sizeof(float));
//   y = (float*)malloc(N*sizeof(float));

//   cudaMalloc(&d_x, N*sizeof(float)); 
//   cudaMalloc(&d_y, N*sizeof(float));

//   for (int i = 0; i < N; i++) {
//     x[i] = 1.0f;
//     y[i] = 2.0f;
//   }

//   cudaMemcpy(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
//   cudaMemcpy(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

//   // Perform SAXPY on 1M elements
//   saxpy<<<(N+255)/256, 256>>>(N, 2.0f, d_x, d_y);

//   cudaMemcpy(y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost);

//   float maxError = 0.0f;
//   for (int i = 0; i < N; i++)
//     maxError = max(maxError, abs(y[i]-4.0f));
//   printf("Max error: %f\n", maxError);

//   cudaFree(d_x);
//   cudaFree(d_y);
//   free(x);
//   free(y);
// }