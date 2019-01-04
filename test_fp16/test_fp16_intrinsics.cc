#include <immintrin.h>
#include <stdint.h>   // uint16_t
#include <cmath>      // fabs
#include <cstdio>     // printf
#include <stdlib.h>   // rand
#include <ctime>      // time

inline uint16_t* bf16_alloc(size_t size){
  // TODO set alignment to 256/512, it's performance may be better.
  //size must be an integral multiple of 64.
  if (size % 256 == 0) {
    return reinterpret_cast<uint16_t*>(aligned_alloc(256, size));
  }
  else {
    size_t new_size = (size / 256 + 1 ) * 256;
    return reinterpret_cast<uint16_t*>(aligned_alloc(256, new_size));
  }
}

inline void convert_f32_to_f16(__m512 src, __m256i* dst) {
  // round to nearest, and suppress exceptions
  *dst = _mm512_cvtps_ph(src, _MM_FROUND_TO_NEAREST_INT);
}

inline void convert_f32_to_f16(__m256 src, __m128i* dst) {
  // round to nearest, and suppress exceptions
  *dst = _mm256_cvtps_ph(src, _MM_FROUND_TO_NEAREST_INT);
}

inline void convert_f32_to_f16(float src, unsigned short* dst) {
  *dst = _cvtss_sh(src, 0);
}

inline void convert_f16_to_f32(__m256i src, __m512* dst) {
  *dst = _mm512_cvtph_ps(src);
}

inline void convert_f16_to_f32(__m128i src, __m256* dst) {
  *dst = _mm256_cvtph_ps(src);
}

inline void convert_f16_to_f32(unsigned short src, float* dst) {
  *dst = _cvtsh_ss(src);
}

bool check_equal(const unsigned int a, const uint16_t b){
  uint16_t short_a = a>>16;
  return short_a == b;
}

bool check_equal(const unsigned int a, const unsigned int b){
  uint16_t short_a = a>>16;
  uint16_t short_b = b >>16;
  return short_a == short_b;
}

void cal_max_min_var(const float* src, const float* dst, int len, float* max_v, float* min_v) {
  for(int i=0; i < len; i++){
    float tmp = fabs(src[i] - dst[i]);
    if(tmp > 0.000001 && tmp / fabs(src[i]) > 0.1) {
      printf("var is bigger than 0.1, i:%d, %f, %f\n", i, src[i], dst[i]);
    }
    if (tmp > *max_v) {
      *max_v = tmp;
    }
    if (tmp < *min_v) {
      *min_v = tmp;
    }
  }
}

void FP32ToFP16(const float* src, uint16_t* dst, int len, int type_flag){
  switch(type_flag)
  {
    case 0:
      {
        int i=0;
        for(; i < (len / 16) * 16; i += 16){
          convert_f32_to_f16(*(__m512*)(src+i), (__m256i*)(dst+i));
        }
        // process the remaining data
        for(; i < len; i++){
          convert_f32_to_f16(*(src+i), (unsigned short*)(dst+i));
        }
      }
      break;
    case 1:
      {
        int i=0;
        for(; i < (len / 8) * 8; i += 8){
          convert_f32_to_f16(*(__m256*)(src+i), (__m128i*)(dst+i));
        }
        // process the remaining data
        for(; i < len; i++){
          convert_f32_to_f16(*(src+i), (unsigned short*)(dst+i));
        }
      }
      break;
    default:
      {
        for(int i=0; i < len; i++){
          convert_f32_to_f16(*(src+i), (unsigned short*)(dst+i));
        }
      }
      break;
  }
}

void FP16ToFP32(const uint16_t* src, float* dst, int len, int type_flag){
  switch(type_flag)
  {
    case 0:
      {
        int i=0;
        for(; i < (len / 16) * 16; i += 16) {
          convert_f16_to_f32(*(__m256i*)(src+i), (__m512*)(dst+i));
        }
        // process the remaining data
        for(; i < len; i++) {
          convert_f16_to_f32(*(unsigned short*)(src+i), (float*)(dst+i));
        }
      }
      break;
    case 1:
      {
        int i=0;
        for(; i < (len / 8) * 8; i += 8) {
          convert_f16_to_f32(*(__m128i*)(src+i), (__m256*)(dst+i));
        }
        // process the remaining data
        for(; i < len; i++) {
          convert_f16_to_f32(*(unsigned short*)(src+i), (float*)(dst+i));
        }
      }
      break;
    default:
      {
        for(int i=0; i < len; i++) {
          convert_f16_to_f32(*(unsigned short*)(src+i), (float*)(dst+i));
        }
      }
      break;
  }
}

void test_fp32Tofp16(int len) {
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  FP32ToFP16(reinterpret_cast<const float*>(src0), dst0, len, 0);
  FP32ToFP16(reinterpret_cast<const float*>(src0), dst1, len, 1);
  // check equal
  bool equal_flag = true;
  for(int i=0; i < len; i++) {
    if (dst0[i] !=  dst1[i]) {
      equal_flag = false;
      printf("convert f32 to f16, cvt0 VS cvt1 is not equal i:%d, %x, %x\n", i, dst0[i], dst1[i]);
      break;
    }
    if ((2 * i) % len == 0){
        printf("convert f32 to f16, %x, %x\n", dst0[i], dst1[i]);
    }
  }
  if (equal_flag) {
    printf("convert fp32 to f16, cvt0 VS cvt1 is equal\n");
  } else {
    printf("convert fp32 to f16, cvt0 VS cvt1 is not equal\n");
  }
  free(src0);
  free(dst0);
  free(dst1);
}

void test_fp16Tofp32(int len) {
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len * sizeof(uint16_t)));
  unsigned int* dst0 = reinterpret_cast<unsigned int*>(bf16_alloc(len * sizeof(unsigned int)));
  unsigned int* dst1 = reinterpret_cast<unsigned int*>(bf16_alloc(len * sizeof(unsigned int)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
  }
  FP16ToFP32(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst0), len, 0);
  FP16ToFP32(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst1), len, 2);
  // check equal
  bool equal_flag = true;
  for(int i=0; i < len; i++) {
    if (dst0[i] !=  dst1[i]) {
      equal_flag = false;
      printf("convert f16 to f32, cvt0 VS cvt1 is not equal i:%d, %x, %x\n", i, dst0[i], dst1[i]);
      break;
    }
    if ((2 * i) % len == 0){
        printf("convert f16 to f32, %x, %x\n", dst0[i], dst1[i]);
    }
  }
  if (equal_flag) {
    printf("convert fp16 to f32, cvt0 VS cvt1 is equal\n");
  } else {
    printf("convert fp16 to f32, cvt0 VS cvt1 is not equal\n");
  }
  free(src0);
  free(dst0);
  free(dst1);
}

void test_float_variance(int len) {
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  float* dst1 = reinterpret_cast<float*>(bf16_alloc(len*sizeof(float)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  FP32ToFP16(reinterpret_cast<const float*>(src0), dst0, len, 0);
  FP16ToFP32(reinterpret_cast<const uint16_t*>(dst0), dst1, len, 0);
  // compare the diff between src and dst1
  float max_diff = -1;
  float min_diff = 100;
  cal_max_min_var(reinterpret_cast<const float*>(src0), reinterpret_cast<const float*>(dst1), len, &max_diff, &min_diff);
  printf("fp32 to fp16 range: max: %f, min: %f\n", max_diff, min_diff);
}

int main() {
  for(int len = 100; len< 10000000; len *= 10){
//    // test fp32 to fp16
//    test_fp32Tofp16(len);
//    // test fp16 to fp32
//    test_fp16Tofp32(len);
    // test variance of float
    test_float_variance(len);
  }
}