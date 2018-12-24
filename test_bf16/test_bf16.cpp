#include <immintrin.h>
#include<stdio.h>
#include<vector>
#include<string.h>    //memset
#include <time.h>

using std::vector;

float average(const vector<double> &timing) {
  double avg = 0;
  for(auto it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

  return avg;
}

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

template<class type>
void print_256(char* name, type *val8)
{
    printf ("%s:", name);
    int i;
    for (i=0; i<8; i++) {
        printf(" %x", val8[i]);
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

//    convert_f32_to_b16(&temp, *(__m256i*)src0, *(__m256i*)src1);
//    convert_b16_to_f32((__m256i*)dst0, (__m256i*)dst1, temp);
//
//    print_256("src0", src0);
//    print_256("src1", src1);
//    print_256("dst0", dst0);
//    print_256("dst1", dst1);

    unsigned int a0[8] = {0x7aaa7bbb, 0x8aaabbbb, 0xaaaabbbb, 0xaaaabbbb,
                          0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb};
    unsigned int a1[8] = {0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb,
                          0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb};
    unsigned int b0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int b1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    convert_f32_to_b16(&temp, *(__m256i*)a0, *(__m256i*)a1);
    convert_b16_to_f32((__m256i*)b0, (__m256i*)b1, temp);
    print_256("a0", a0);
    print_256("b0", b0);
    print_256("a1", a1);
    print_256("b1", b1);

    vector<double> f32tobf16_times, bf16tof32_times;
    struct timespec start, mid, stop;
    memset(&start, 0, sizeof(struct timespec));
    memset(&mid, 0, sizeof(struct timespec));
    memset(&stop, 0, sizeof(struct timespec));
    for(int i=0; i<10000; i++){
      clock_gettime(CLOCK_REALTIME, &start);
      convert_f32_to_b16(&temp, *(__m256i*)a0, *(__m256i*)a1);
      clock_gettime(CLOCK_REALTIME, &mid);
      convert_b16_to_f32((__m256i*)b0, (__m256i*)b1, temp);
      clock_gettime(CLOCK_REALTIME, &stop);
      const double f32tobf16_time = (mid.tv_sec - start.tv_sec) * 1000000000 + (mid.tv_nsec -start.tv_nsec);
      const double bf16tof32_time = (stop.tv_sec - mid.tv_sec) * 1000000000 + (stop.tv_nsec - mid.tv_nsec);
      f32tobf16_times.push_back(f32tobf16_time);
      bf16tof32_times.push_back(bf16tof32_time);
    }
    float avg_f32tobf16_time = average(f32tobf16_times);
    float avg_bf16tof32_time = average(bf16tof32_times);
    printf("f32 convert to bf16 avg time: %f us\n", avg_f32tobf16_time);
    printf("bf16 convert to f32 avg time: %f us\n", avg_bf16tof32_time);

}