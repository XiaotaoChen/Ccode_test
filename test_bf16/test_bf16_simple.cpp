#include <x86intrin.h>
#include <stdio.h>
#include<string.h>    //memset
#include<vector>
#include<time.h>

using std::vector;

float average(const vector<double> &timing) {
  double avg = 0;
  for(auto it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

  return avg;
}

__m256i cvt_f32_b16(__m512i x)
{
  x = _mm512_bsrli_epi128(x, 2);
  return _mm512_cvtepi32_epi16(x);
}

__m512i cvt_b16_f32(__m256i x)
{
  __m512i y = _mm512_cvtepu16_epi32(x);
  return _mm512_bslli_epi128(y, 2);
}
template<class type>
void print_256(char* name, type *val8, int len)
{
    printf ("%s:", name);
    int i;
    for (i=0; i<len; i++) {
        printf(" %x", val8[i]);
    }
    printf ("\n");
}

int main() {

  alignas(64) unsigned int a0[16] = { 0x7aaa7bbb, 0x8aaabbbb, 0xaaaabbbb, 0xaaaabbbb,
    0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb,
    0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb };
  alignas(64) short a1[16];
  alignas(64) int a2[16];

  __m512i f32 = *(__m512i *)a0;
  __m256i b16 = cvt_f32_b16(f32);
  *(__m256i *)a1 = b16;

  __m512i f32_new = cvt_b16_f32(b16);
  *(__m512i *)a2 = f32_new;

   print_256<unsigned int>("a0", a0, 16);
   print_256<int>("a2", a2, 16);

  vector<double> f32tobf16_times, bf16tof32_times;
  struct timespec start, mid, stop;
  memset(&start, 0, sizeof(struct timespec));
  memset(&mid, 0, sizeof(struct timespec));
  memset(&stop, 0, sizeof(struct timespec));
  for (int i=0; i<10000; i++){
    clock_gettime(CLOCK_REALTIME, &start);
    __m512i f32 = *(__m512i *)a0;
    __m256i b16 = cvt_f32_b16(f32);
    clock_gettime(CLOCK_REALTIME, &mid);
    __m512i f32_new = cvt_b16_f32(b16);
    *(__m512i *)a2 = f32_new;
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

  return 0;
}
