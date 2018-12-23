#include <immintrin.h>
void convert_f32_to_b16(__m256i *dst, __m256i src0, __m256i src1)
{
    src0 = _mm256_srli_epi32(src0, 16);
    src1 = _mm256_srli_epi32(src1, 16);
    *dst = _mm256_packus_epi32(src0, src1);
}

void convert_b16_to_f32(__m256i *dst0, __m256i *dst1, __m256i src)
{
    int zero[8] = {0,0,0,0,0,0,0,0};
    __m256i zeros = *(__m256i*)zero;
    *dst0 = _mm256_unpacklo_epi16(zeros, src);
    *dst1 = _mm256_unpackhi_epi16(zeros, src);
}

void print_256(char* name, float *val8)
{
    printf ("%s:", name);
    int i;
    for (i=0; i<8; i++) {
        printf(" %f", val8[i]);
    }
    printf ("\n");
}

int main(void)
{
    float src0[]={1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8};
    float src1[]={2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8};
    float dst0[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float dst1[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    __m256i temp;

    convert_f32_to_b16(&temp, *(__m256i*)src0, *(__m256i*)src1);
    convert_b16_to_f32((__m256i*)dst0, (__m256i*)dst1, temp);

    print_256("src0", src0);
    print_256("src1", src1);
    print_256("dst0", dst0);
    print_256("dst1", dst1);
}

