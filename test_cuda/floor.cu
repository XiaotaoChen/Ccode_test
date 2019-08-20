#include <stdio.h>

__global__
void tofloor(int n, float* a, float* b, float* smin, float* quant_unit) {
    *b = floor((*a - *smin)/(*quant_unit) + 0.5);
}

__global__
void toclamp(int n, float* a, float* b, float* smin) {
    // *b = clamp(*a, *smin, 0);
    // *b = max(*a, *smin);
    *b = max(0.22199318, -100000000.0);
}

int main() {
    float a = 0.22199318;
    float smin = -100000000;
    float quant_unit = 781250.0;
    float* a_d, *b_d, *smin_d, *quant_unit_d;
    cudaMalloc((void**)&a_d, sizeof(float));
    cudaMalloc((void**)&smin_d, sizeof(float));
    cudaMalloc((void**)&quant_unit_d, sizeof(float));
    cudaMalloc((void**)&b_d, sizeof(float));
    cudaMemcpy(a_d, &a, sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(smin_d, &smin, sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(quant_unit_d, &quant_unit, sizeof(float), cudaMemcpyHostToDevice);

    cudaMemcpy(&a, a_d, sizeof(float), cudaMemcpyDeviceToHost);
    printf("a:%.lf\n", a);

    int N = 1;
    // tofloor<<<(N+255)/256, 256>>>(N, a_d, b_d, smin_d, quant_unit_d);
    toclamp<<<(N+255)/256, 256>>>(N, a_d, b_d, smin_d);

    float* b;
    b = (float*) malloc(sizeof(float));
    
    cudaMemcpy(b, b_d, sizeof(float), cudaMemcpyDeviceToHost);
    printf("a:%lf, b:%.lf\n", a, *b);

    free(b);
    cudaFree(a_d);
    cudaFree(b_d);



    return 0;
}