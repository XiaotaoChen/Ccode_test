#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<vector>
#include<memory.h>

using std::vector;

float average(const vector<double> &timing) {
  double avg = 0;
  for(auto it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

  return avg;
}

inline void convert_f32_to_b16(__m512i src, __m256i* dest)
{
  __m512i y = _mm512_bsrli_epi128(src, 2);
  *dest = _mm512_cvtepi32_epi16(y);
}

inline void convert_b16_to_f32(__m256i src, __m512i* dest)
{
  __m512i y = _mm512_cvtepu16_epi32(src);
  *dest = _mm512_bslli_epi128(y, 2);
}

inline void convert_f32_to_b16(__m256i src0, __m256i src1, __m256i *dst)
{
    src0 = _mm256_srli_epi32(src0, 16);
    src1 = _mm256_srli_epi32(src1, 16);
    *dst = _mm256_packus_epi32(src0, src1);
}

inline void convert_b16_to_f32(__m256i src, __m256i *dst0, __m256i *dst1)
{
    int zero[8] = {0,0,0,0,0,0,0,0};
    __m256i zeros = *(__m256i*)zero;
    *dst0 = _mm256_unpacklo_epi16(zeros, src);
    *dst1 = _mm256_unpackhi_epi16(zeros, src);
}

inline void BF16ToFloat(unsigned short* src, float* dest, int len, int type_flag){
 switch (type_flag)
 {
   case 0:
     for(int i=0; i < len; i+=16){
       convert_b16_to_f32(*(__m256i*)(src+i), (__m512i*)(dest+i));
     }
     break;
   case 1:
     for(int i=0; i < len; i+=16){
       convert_b16_to_f32(*(__m256i*)(src+i), (__m256i*)(dest+i), (__m256i*)(dest+i+8));
     }
     break;
   default:
     unsigned int* dest_unsigned = reinterpret_cast<unsigned int*>(dest);
     for(int i=0; i<len; i++){
       *(dest_unsigned+i) = *(src+i)<<16;
     }
     break;
 }
}

inline void FloatToBF16(float* src, unsigned short* dest, int len, int type_flag){
 switch (type_flag)
 {
   case 0:
     for(int i=0; i < len; i+=16){
       convert_f32_to_b16(*(__m512i*)(src+i), (__m256i*)(dest+i));
     }
     break;
   case 1:
     for(int i=0; i < len; i+=16){
       convert_f32_to_b16(*(__m256i*)(src+i), *(__m256i*)(src+i+8), (__m256i*)(dest+i));
     }
     break;
  default:
     unsigned int* src_unsigned = reinterpret_cast<unsigned int*>(src);
     for(int i=0; i<len; i++){
       *(dest+i) = *(src_unsigned+i)>>16;
     }
     break;
 }
}

bool check_equal(unsigned int a, unsigned short b){
  unsigned short short_a = a>>16;
  return short_a == b;
}
bool check_equal(unsigned int a, unsigned int b){
  unsigned short short_a = a>>16;
  unsigned short short_b = b>>16;
  return short_a == short_b;
}

void test_len(int len, int type_flag){
//  alignas(64) unsigned int a0[len];
  unsigned int* a0 = reinterpret_cast<unsigned int*>(aligned_alloc(64, len*sizeof(unsigned int)));
  for(int i=0; i < len; i++){
    a0[i] = 0x7aaa7bbb;
  }
//  alignas(64) unsigned short a1[len] = {0};
//  alignas(64) unsigned int a2[len];
  unsigned short* a1 = reinterpret_cast<unsigned short*>(aligned_alloc(64, len*sizeof(unsigned short)));
  unsigned int* a2 = reinterpret_cast<unsigned int*>(aligned_alloc(64, len*sizeof(unsigned int)));

  FloatToBF16(reinterpret_cast<float*>(a0), a1, len, type_flag);
  BF16ToFloat(a1, reinterpret_cast<float*>(a2), len, type_flag);
  //check equal
  for(int i=0; i < len; i++){
    if(!check_equal(a0[i], a2[i])){
      printf("%d, %x\n", i, a0[i]);
      printf("%d, %x\n", i, a2[i]);
    }
  }

  vector<double> f32tobf16_times, bf16tof32_times;
  struct timespec start, mid, stop;
  memset(&start, 0, sizeof(struct timespec));
  memset(&mid, 0, sizeof(struct timespec));
  memset(&stop, 0, sizeof(struct timespec));
  for(int i=0; i< 100; i++){
    clock_gettime(CLOCK_REALTIME, &start);
    FloatToBF16(reinterpret_cast<float*>(a0), a1, len, type_flag);
    clock_gettime(CLOCK_REALTIME, &mid);
    BF16ToFloat(a1, reinterpret_cast<float*>(a2), len, type_flag);
    clock_gettime(CLOCK_REALTIME, &stop);
    const double f32tobf16_time = (mid.tv_sec - start.tv_sec) * 1000000000 + (mid.tv_nsec -start.tv_nsec);
    const double bf16tof32_time = (stop.tv_sec - mid.tv_sec) * 1000000000 + (stop.tv_nsec - mid.tv_nsec);
    f32tobf16_times.push_back(f32tobf16_time);
    bf16tof32_times.push_back(bf16tof32_time);
   }
  float avg_f32tobf16_time = average(f32tobf16_times);
  float avg_bf16tof32_time = average(bf16tof32_times);
  printf("len:%d f32 convert to bf16 avg time: %f us\n", len, avg_f32tobf16_time);
  printf("len:%d bf16 convert to f32 avg time: %f us\n", len, avg_bf16tof32_time);
  free(a0);
  free(a1);
  free(a2);
}

int main(){
  for(int i=128; i<=10000000; i*=10){
    test_len(i, 0);
  }
  for(int i=128; i<=10000000; i*=10){
    test_len(i, 1);
  }
  for(int i=128; i<=10000000; i*=10){
    test_len(i, 2);
  }
}