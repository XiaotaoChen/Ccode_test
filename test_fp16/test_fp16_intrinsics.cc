#include <immintrin.h>
#include <stdint.h>   // uint16_t
#include <cmath>      // fabs
#include <cstdio>     // printf
#include <stdlib.h>   // rand
#include <vector>
#include <cstring>    // memcpy
#include "../utils/utils.h"

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

bool check_equal(const uint16_t a, const uint16_t b){
  uint8_t short_a = a>>8;
  uint8_t short_b = b>>8;
  return short_a == short_b;
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
//    if(tmp > 0.000001 && tmp / fabs(src[i]) > 0.1) {
//      printf("var is bigger than 0.1, i:%d, %f, %f\n", i, src[i], dst[i]);
//    }
    if (tmp > *max_v) {
      *max_v = tmp;
    }
    if (tmp < *min_v) {
      *min_v = tmp;
    }
  }
}

void mask_fp16(uint16_t* src, int size, int low_bits) {
 uint16_t mask_code = 0xffff;
 for(int i = 0; i < low_bits; i++) {
   mask_code &= ~(1U << i);
 }
 for(int i=0; i< size; i++, src+=1) {
   *src = (*src) & mask_code;
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
  uint16_t* dst0_mask = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  float* dst1 = reinterpret_cast<float*>(bf16_alloc(len*sizeof(float)));
  float* dst1_mask = reinterpret_cast<float*>(bf16_alloc(len*sizeof(float)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  FP32ToFP16(reinterpret_cast<const float*>(src0), dst0, len, 0);
  memcpy(dst0_mask, dst0, len * sizeof(uint16_t));
  mask_fp16(dst0_mask, len, 8);
  FP16ToFP32(reinterpret_cast<const uint16_t*>(dst0), dst1, len, 0);
  FP16ToFP32(reinterpret_cast<const uint16_t*>(dst0_mask), dst1_mask, len, 0);
  // compare the diff between src and dst1
  float max_diff = -1;
  float min_diff = 100;
  cal_max_min_var(reinterpret_cast<const float*>(dst1_mask), reinterpret_cast<const float*>(dst1), len, &max_diff, &min_diff);
  printf("fp32 to fp16 range: max: %f, min: %f\n", max_diff, min_diff);

  free(src0);
  free(dst0);
  free(dst1);
}

double test_f32Tof16_time(int len, int type_flag){
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  FP32ToFP16(reinterpret_cast<const float*>(src0), dst0, len, type_flag);
  tmp_time->stop();
  free(src0);
  free(dst0);
  return tmp_time->get_time();
}

double test_f16Tof32_time(int len, int type_flag){
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len * sizeof(uint16_t)));
  unsigned int* dst0 = reinterpret_cast<unsigned int*>(bf16_alloc(len * sizeof(unsigned int)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
    src0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  FP16ToFP32(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst0), len, type_flag);
  tmp_time->stop();
  return tmp_time->get_time();
}

void test_mask_fp16(int len) {
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len * sizeof(uint16_t)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len * sizeof(uint16_t)));
  unsigned int* src0_fp32 = reinterpret_cast<unsigned int*>(bf16_alloc(len * sizeof(unsigned int)));
  unsigned int* dst0_fp32 = reinterpret_cast<unsigned int*>(bf16_alloc(len * sizeof(unsigned int)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++) {
//    src0[i] = 0x7aaa;
    src0[i] = rand();
  }
  memcpy(dst0, src0, len * sizeof(uint16_t));
  mask_fp16(dst0, len, 8);
  bool equal_flag = true;
  for(int i = 0; i < len; i++) {
    equal_flag = check_equal(src0[i], dst0[i]);
    if(!equal_flag) {
      printf("i: %d, src, dst: %x, %x is not equal \n", i, src0[0], dst0[i]);
    }
//    printf("src, dst: %x, %x\n", src0[i], dst0[i]);
  }
  if(equal_flag) {
    printf("len: %d mask fp16 is equal\n", len);
  }

  float* src0_f = reinterpret_cast<float*>(src0_fp32);
  float* dst0_f = reinterpret_cast<float*>(dst0_fp32);
  FP16ToFP32(src0, src0_f, len, 0);
  FP16ToFP32(dst0, dst0_f, len, 0);
  float max_diff = -1;
  float min_diff = 100;
  cal_max_min_var(reinterpret_cast<const float*>(src0_f), reinterpret_cast<const float*>(dst0_f), len, &max_diff, &min_diff);
  printf("fp32 to fp16 range: max: %f, min: %f\n", max_diff, min_diff);

  free(src0);
  free(dst0);
  free(src0_fp32);
  free(dst0_fp32);
}

void test_fp32_mask_fp16_diff(int len) {
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  unsigned int* dst1 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));

  float* src0_fp32 = reinterpret_cast<float*>(src0);
  float* dst1_fp32 = reinterpret_cast<float*>(dst1);

  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
//    src0[i] = rand();
    src0_fp32[i] = i * 0.121234334;
//    printf("src0 i: %d, %f\n", i, src0_fp32[i]);
  }

  FP32ToFP16(src0_fp32, dst0, len, 0);
  mask_fp16(dst0, len, 8);
  FP16ToFP32(dst0, dst1_fp32, len, 0);
  float max_diff = -1;
  float min_diff = 100;
  cal_max_min_var(reinterpret_cast<const float*>(src0_fp32), reinterpret_cast<const float*>(dst1_fp32), len, &max_diff, &min_diff);
  printf("fp32 to fp16 range: max: %f, min: %f\n", max_diff, min_diff);

  free(src0);
  free(dst0);
  free(dst1);
}

int main() {
  for(int len = 100; len< 10000000; len *= 10){
//  for(int len = 100; len< 1000; len *= 10){
//    // test fp32 to fp16
//    test_fp32Tofp16(len);
//    // test fp16 to fp32
//    test_fp16Tofp32(len);
//    // test variance of float
//    test_float_variance(len);
//    // test mask fp16 to uint8
//    test_mask_fp16(len);
    // test the diff between fp32 and mask fp16
    test_fp32_mask_fp16_diff(len);
     // test time
//     for(int type_flag=0; type_flag < 3; type_flag++){
//       std::vector<double> f32tof16_times, f16tof32_times;
//       for(int i=0; i< 100; i++){
//         double f32tof16_time = test_f32Tof16_time(len, type_flag);
//         double f16tof32_time = test_f16Tof32_time(len, type_flag);
//         f32tof16_times.push_back(f32tof16_time);
//         f16tof32_times.push_back(f16tof32_time);
//       }
//       float avg_f32tof16_time = utils::average(f32tof16_times);
//       float avg_f16tof32_time = utils::average(f16tof32_times);
//       printf("len:%d type_flag:%d, f32 convert to f16 avg time: %f us\n", len, type_flag, avg_f32tof16_time);
//       printf("len:%d type_flag:%d, f16 convert to f32 avg time: %f us\n", len, type_flag, avg_f16tof32_time);
//     }
  }
}