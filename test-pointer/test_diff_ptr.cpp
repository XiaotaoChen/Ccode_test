#include <stdio.h>
#include <stdlib.h>

template <typename DType>
void print_arr(DType* data, int size, int type_flag){
    switch(type_flag)
    {
        case 0:
            {
                for ( int i = 0; i< size; i++) {
                    printf("%d, ", data[i]);
                }
            }
            break;
        case 1:
            {
                for ( int i = 0; i< size; i++) {
                    printf("%lf, ", data[i]);
                }
            }
            break;
        case 2:
            {
                for ( int i = 0; i< size; i++) {
                    printf("%f, ", data[i]);
                }
            }
            break;
        default:
            break;
    }
    printf("\n");
}

int main() {
    int size = 10;
    float* fp;
    int* intp;
    double* dp;
    fp = (float*)malloc(sizeof(float) * size);
    intp = (int*)malloc(sizeof(int) * size);
    dp = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        fp[i] = i;
        intp[i] = i * 2;
        dp[i] = i * 3;
    }
    print_arr<int>(intp, size, 0);
    print_arr<float>(fp, size, 1);
    print_arr<double>(dp, size, 2);

    printf("fp addr:%p, +1: %p\n", fp, fp +1);
    printf("intp addr:%p, +1: %p\n", intp, intp +1);
    printf("dp addr:%p, +1: %p\n", dp, dp +1);
    void* vp = static_cast<void*>(fp);
    printf("void fp addr:%p, +1: %p\n", vp, vp +1);
    vp = static_cast<void*>(intp);
    printf("void intp addr:%p, +1: %p\n", vp, vp +1);
    vp = static_cast<void*>(dp);
    printf("void dp addr:%p, +1: %p\n", vp, vp +1);

    return 0;
}