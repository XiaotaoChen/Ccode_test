#include <immintrin.h>
#include <stdint.h>  // uint16_t
#include <stdlib.h>  // rand
#include <cstdio> // printf
#include <cmath> // fabs
#include <ctime>  // time
#include <vector>  // vector
#include <string> // string
#include "../utils/utils.h"  // for calculate time

inline uint16_t* bf16_alloc(size_t size, int alignment){
  // TODO set alignment to 256/512, it's performance may be better.
  //size must be an integral multiple of 64.
  if (size % alignment == 0) {
    return reinterpret_cast<uint16_t*>(aligned_alloc(alignment, size));
  }
  else {
    size_t new_size = (size / alignment + 1 ) * alignment;
    return reinterpret_cast<uint16_t*>(aligned_alloc(alignment, new_size));
  }
}

inline void convert_f32_to_b16(const void* src, void* dst)
{
  __m512i y = _mm512_bsrli_epi128(_mm512_loadu_si512(src), 2);
  _mm256_storeu_si256((__m256i*)(dst), _mm512_cvtepi32_epi16(y));
}

inline void convert_b16_to_f32(const void* src, void* dst)
{
//  __m256i aligned_m256i = _mm256_loadu_si256((__m256i const*)src);
//  __m512i y = _mm512_cvtepu16_epi32(aligned_m256i);
//  __m512i aligned_m512i = _mm512_bslli_epi128(y, 2);
//  _mm512_storeu_si512(dst, aligned_m512i);
  __m512i y = _mm512_cvtepu16_epi32(_mm256_loadu_si256((__m256i const*)src));
  _mm512_storeu_si512(dst, _mm512_bslli_epi128(y, 2));
}

inline void convert_f32_to_b16(const void* src0, const void* src1, void *dst)
{
    __m256i aligned_m256i_src0 = _mm256_srli_epi32(_mm256_loadu_si256((__m256i const*)src0), 16);
    __m256i aligned_m256i_src1 = _mm256_srli_epi32(_mm256_loadu_si256((__m256i const*)src1), 16);
    _mm256_storeu_si256((__m256i*)(dst), _mm256_packus_epi32(aligned_m256i_src0, aligned_m256i_src1));
}

inline void convert_b16_to_f32(const void* src, void *dst0, void *dst1)
{
    int zero[8] = {0,0,0,0,0,0,0,0};
    __m256i aligned_m256i_src = _mm256_loadu_si256((__m256i const*)src);
    __m256i aligned_m256i_zeros = _mm256_loadu_si256((__m256i const*) zero);
    _mm256_storeu_si256((__m256i*)(dst0), _mm256_unpacklo_epi16(aligned_m256i_zeros, aligned_m256i_src));
    _mm256_storeu_si256((__m256i*)(dst1), _mm256_unpackhi_epi16(aligned_m256i_zeros, aligned_m256i_src));
}

inline void convert_f32_to_b16(__m512i* src, __m256i* dst)
{
  __m512i y = _mm512_bsrli_epi128(*src, 2);
  *dst = _mm512_cvtepi32_epi16(y);
}

inline void convert_b16_to_f32(__m256i* src, __m512i* dst)
{
  __m512i y = _mm512_cvtepu16_epi32(*src);
  *dst = _mm512_bslli_epi128(y, 2);
}

inline void convert_f32_to_b16(__m256i* src0, __m256i* src1, __m256i *dst)
{
    *src0 = _mm256_srli_epi32(*src0, 16);
    *src1 = _mm256_srli_epi32(*src1, 16);
    *dst = _mm256_packus_epi32(*src0, *src1);
}

inline void convert_b16_to_f32(__m256i* src, __m256i *dst0, __m256i *dst1)
{
    int zero[8] = {0,0,0,0,0,0,0,0};
    __m256i zeros = *(__m256i*)zero;
    *dst0 = _mm256_unpacklo_epi16(zeros, *src);
    *dst1 = _mm256_unpackhi_epi16(zeros, *src);
}

bool is_aligned(const void* ptr, int alignment) {
  auto iptr = reinterpret_cast<uintptr_t>(ptr);
  return !(iptr % alignment);
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

float cal_var_range(const unsigned int a, const uint16_t b){
  const float* fp_a = reinterpret_cast<const float*>(&a);
  const unsigned int int_b = b<<16;
  const float* fp_b = reinterpret_cast<const float*>(&int_b);
  float abs_err = fabs((*fp_a) - (*fp_b));
  float var = 0;
  if (fabs(*fp_a) > 0.00001){
    var = abs_err / fabs(*fp_a);
  }
  if (var > 0.1) {
    printf("range is larger than 0.1 , (a, b) %f, %f, %x, %x, abs_err: %f, range: %f\n", *fp_a, *fp_b, a, int_b, abs_err, var);
  }
  return var;
}

void cal_min_max_var(const unsigned int* fp32_p,
                     const uint16_t* bf16_p,
                     int len,
                     float* min_var,
                     float* max_var){
  for (int i = 0; i < len; i++) {
    float temp = cal_var_range(*(fp32_p + i), *(bf16_p + i));
    if (temp < *min_var) {
      *min_var = temp;
    }
    if (temp > *max_var) {
      *max_var = temp;
    }
  }
}

void BF16ToFloat(const uint16_t* src, float* dst, int len, int type_flag){
 bool aligned_flag = is_aligned(reinterpret_cast<const void*>(src), 64)
                     && is_aligned(reinterpret_cast<const void*>(dst), 64);
 switch (type_flag)
 {
   case 0:
     {
       int i;
       if (aligned_flag) {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_b16_to_f32((__m256i*)(src+i), (__m512i*)(dst+i));
         }
       } else {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_b16_to_f32((const void*)(src+i), (void*)(dst+i));
         }
       }
       // process the remaining data
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       for(i = (len / 16) * 16; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
   case 1:
     {
       int i;
       if (aligned_flag) {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_b16_to_f32((__m256i*)(src+i), (__m256i*)(dst+i), (__m256i*)(dst+i+8));
         }
       } else {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_b16_to_f32((const void*)(src+i), (void*)(dst+i), (void*)(dst+i+8));
         }
       }
       // process the remaining data
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       for(i = (len / 16) * 16; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
   default:
     {
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       int i;
       for(i=0; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
 }
}

void FloatToBF16(const float* src, uint16_t* dst, int len, int type_flag){
 bool aligned_flag = is_aligned(reinterpret_cast<const void*>(src), 64)
                     && is_aligned(reinterpret_cast<const void*>(dst), 64);
 switch (type_flag)
 {
   case 0:
     {
       int i;
       if (aligned_flag) {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_f32_to_b16((__m512i*)(src+i), (__m256i*)(dst+i));
         }
       } else {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_f32_to_b16((const void*)(src+i), (void*)(dst+i));
         }
       }
       // process the remaining data
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       for(i = (len / 16) * 16; i < len; i++){
         *(dst+i) = *(src_unsigned+i)>>16;
       }
     }
     break;
   case 1:
     {
       int i;
       if (aligned_flag) {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_f32_to_b16((__m256i*)(src+i), (__m256i*)(src+i+8), (__m256i*)(dst+i));
         }
       } else {
         for(i = 0; i < (len / 16) * 16; i += 16){
           convert_f32_to_b16((const void*)(src+i), (const void*)(src+i+8), (void*)(dst+i));
         }
       }
       // process the remaining data
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       for(i = (len / 16) * 16; i < len; i++){
         *(dst+i) = *(src_unsigned+i)>>16;
       }
     }
     break;
   default:
     {
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       int i;
       for(i=0; i < len; i++){
         *(dst+i) = *(src_unsigned+i)>>16;
       }
     }
     break;
 }
}

void BF16ToFloat_naive(const uint16_t* src, float* dst, int size, int type_flag){
  unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
  for(int i=0; i < size; i++){
    *(dst_unsigned+i) = *(src+i)<<16;
  }
}

void FloatToBF16_naive(const float* src, uint16_t* dst, int size, int type_flag){
  const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
  for(int i=0; i < size; i++){
    *(dst+i) = *(src_unsigned+i)>>16;
  }
}

void bf16_sum(void* invec, void* inoutvec, int* len, int type_flag){
  bool aligned_flag = is_aligned(reinterpret_cast<const void*>(invec), 64)
                      && is_aligned(reinterpret_cast<const void*>(inoutvec), 64);
  int i;
  uint16_t* invec_16 = reinterpret_cast<uint16_t*>(invec);
  uint16_t* inoutvec_16 = reinterpret_cast<uint16_t*>(inoutvec);
  if(type_flag == 0){
    if (aligned_flag) {
      for(i=0; i < (*len / 16) * 16; i += 16)
      {
        // convert in & inout to m512
        __m512i in_m512, out_m512;
        convert_b16_to_f32((__m256i*)(invec_16+i), (__m512i*)(&in_m512));
        convert_b16_to_f32((__m256i*)(inoutvec_16+i), (__m512i*)(&out_m512));
        // add them together to new_inout_m256
        __m512 newout_m512 = _mm512_add_ps((__m512)in_m512, (__m512)out_m512);
        // convert back and store in inout
        convert_f32_to_b16((__m512i*)(&newout_m512), (__m256i*)(inoutvec_16+i));
      }
    } else {
      for(i=0; i < (*len / 16) * 16; i += 16)
      {
        // convert in & inout to m512
        __m512i in_m512, out_m512;
        convert_b16_to_f32((void*)(invec_16+i), (void*)(&in_m512));
        convert_b16_to_f32((void*)(inoutvec_16+i), (void*)(&out_m512));
        // add them together to new_inout_m256
        __m512 newout_m512 = _mm512_add_ps((__m512)in_m512, (__m512)out_m512);
        // convert back and store in inout
        convert_f32_to_b16((const void *)(&newout_m512), (void*)(inoutvec_16+i));
      }
    }
  } else if(type_flag == 1){
    if (aligned_flag) {
      for(i=0; i< (*len / 16) * 16; i += 16){
        // convert in & out to m256
        __m256i invec0, invec1, outvec0, outvec1;
        convert_b16_to_f32((__m256i*)(invec_16+i), (__m256i*)(&invec0), (__m256i*)(&invec1));
        convert_b16_to_f32((__m256i*)(inoutvec_16+i), (__m256i*)(&outvec0), (__m256i*)(&outvec1));
        // add them together to new_inout_m256
        __m256 new_inout0_m256 = _mm256_add_ps((__m256)invec0, (__m256)outvec0);
        __m256 new_inout1_m256 = _mm256_add_ps((__m256)invec1, (__m256)outvec1);
        // convert back and store in inout
        convert_f32_to_b16((__m256i*)(&new_inout0_m256), (__m256i*)(&new_inout1_m256), (__m256i*)(inoutvec_16 + i));
      }
    } else {
      for(i=0; i< (*len / 16) * 16; i += 16){
        // convert in & out to m256
        __m256i invec0, invec1, outvec0, outvec1;
        convert_b16_to_f32((const void*)(invec_16 + i), (void*)(&invec0), (void*)(&invec1));
        convert_b16_to_f32((const void*)(inoutvec_16 + i), (void*)(&outvec0), (void*)(&outvec1));
        // add them together to new_inout_m256
        __m256 new_inout0_m256 = _mm256_add_ps((__m256)invec0, (__m256)outvec0);
        __m256 new_inout1_m256 = _mm256_add_ps((__m256)invec1, (__m256)outvec1);
        // convert back and store in inout
        convert_f32_to_b16((const void*)(&new_inout0_m256), (const void*)(&new_inout1_m256), (void*)(inoutvec_16 + i));
      }
    }
  }
  // process the remaining data
  for(i=(*len / 16) * 16; i < *len; i++){
    unsigned int tmp_in = (*(invec_16 + i)) << 16;
    unsigned int tmp_out = (*(inoutvec_16 + i)) << 16;
    float in_float = *reinterpret_cast<float*>(&tmp_in);
    float inout_float = *reinterpret_cast<float*>(&tmp_out);
    inout_float += in_float;
    *(inoutvec_16 + i) = *reinterpret_cast<unsigned int*>(&inout_float)>>16;
  }
}

void bf16_sum_naive(void* invec, void* inoutvec, int* len){
  int i;
  // process the remaining data
  uint16_t* in_short = reinterpret_cast<uint16_t*>(invec);
  uint16_t* out_short = reinterpret_cast<uint16_t*>(inoutvec);
  for(i=0; i < *len; i++){
    unsigned int tmp_in = (*(in_short + i)) << 16;
    unsigned int tmp_out = (*(out_short + i)) << 16;
    float in_float = *reinterpret_cast<float*>(&tmp_in);
    float inout_float = *reinterpret_cast<float*>(&tmp_out);
    inout_float += in_float;
    *(out_short + i) = (*reinterpret_cast<unsigned int*>(&inout_float))>>16;
  }
}

bool check_f32Tob16_equal(const unsigned int* src, const uint16_t* naive_cvt, const uint16_t* intrinsics_cvt, int len){
  for(int i=0; i< len; i++){
    if(!check_equal(*(src+i), *(intrinsics_cvt+i))){
      printf("check f32 to b16 src VS intrinsics is not equal, i: %d, src:%x, intrinsics: %x\n", i, *(src+i), *(intrinsics_cvt+i));
      return false;
    }
    if(*(naive_cvt+i) != *(intrinsics_cvt+i)){
      printf("check f32 to b16 naive VS intrinsics is not equal, i: %d, naive:%x, intrinsics: %x\n", i, *(naive_cvt+i), *(intrinsics_cvt+i));
      return false;
    }
//    if(2*i%len == 0){
//      printf("check f32 to b16, i; %d, fp32: %x, naive bf16: %x, bf16: %x\n", i, *(src+i), *(naive_cvt+i), *(intrinsics_cvt+i));
//    }
  }
  return true;
}

bool check_b16Tof32_equal(const uint16_t* src, const unsigned int* naive_cvt, const unsigned int* intrinsics_cvt, int len){
  for(int i=0; i< len; i++){
    if(!check_equal(*(naive_cvt+i), *(src+i))){
      printf("check b16 to f32 naive VS src is not equal, i: %d, naive:%x, src: %x\n", i, *(naive_cvt+i), *(src+i));
      return false;
    }
    if(!check_equal(*(intrinsics_cvt+i), *(src+i))){
      printf("check b16 to f32 intrinsics VS src is not equal, i: %d, intrinsics:%x, src: %x\n", i, *(intrinsics_cvt+i), *(src+i));
      return false;
    }
//    if(2*i%len == 0){
//        printf("check b16 to f32, i; %d, bf16: %x, naive fp32: %x, fp32: %x\n", i, *(src+i), *(naive_cvt+i), *(intrinsics_cvt+i));
//    }
  }
  return true;
}

void test_f32Tob16(int len, int alignment){
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
   srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  FloatToBF16(reinterpret_cast<const float*>(src0), dst0, len, 2);
  FloatToBF16(reinterpret_cast<const float*>(src0), dst1, len, 0);
  bool f32Tob16_flag = check_f32Tob16_equal(reinterpret_cast<const unsigned int*>(src0),
                                           reinterpret_cast<const uint16_t*>(dst0),
                                           reinterpret_cast<const uint16_t*>(dst1),
                                           len);
  if (f32Tob16_flag){
    printf("size: %d fp32 convert to bf16 is equal !\n", len);
  } else {
    printf("size: %d fp32 convert to bf16 is not equal !\n", len);
  }
  free(src0);
  free(dst0);
  free(dst1);
}

void test_b16Tof32(int len, int alignment){
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  unsigned int* dst0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  unsigned int* dst1 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
   srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
  }
  BF16ToFloat(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst0), len, 2);
  BF16ToFloat(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst1), len, 0);
  bool b16Tof32_flag = check_b16Tof32_equal(reinterpret_cast<const uint16_t*>(src0),
                                            reinterpret_cast<const unsigned int*>(dst0),
                                            reinterpret_cast<const unsigned int*>(dst1),
                                            len);
  if (b16Tof32_flag){
    printf("size: %d bf16 convert to fp32 is equal !\n", len);
  } else {
    printf("size: %d bf16 convert to fp32 is not equal !\n", len);
  }
  free(src0);
  free(dst0);
  free(dst1);
}

void test_cvt1_cvt2_sum_equal(int len, int alignment){
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  unsigned int* src1 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  uint16_t* cvt0_dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* cvt0_dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* cvt1_dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* cvt1_dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
   srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
    src1[i] = rand();
  }
  FloatToBF16(reinterpret_cast<const float*>(src0), cvt0_dst0, len, 0);
  FloatToBF16(reinterpret_cast<const float*>(src0), cvt1_dst0, len, 1);
  FloatToBF16(reinterpret_cast<const float*>(src1), cvt0_dst1, len, 0);
  FloatToBF16(reinterpret_cast<const float*>(src1), cvt1_dst1, len, 1);
  bf16_sum_naive(reinterpret_cast<void*>(cvt0_dst0), reinterpret_cast<void*>(cvt0_dst1), &len);
  bf16_sum_naive(reinterpret_cast<void*>(cvt1_dst0), reinterpret_cast<void*>(cvt1_dst1), &len);
  BF16ToFloat(reinterpret_cast<const uint16_t*>(cvt0_dst1), reinterpret_cast<float*>(src0), len, 0);
  BF16ToFloat(reinterpret_cast<const uint16_t*>(cvt1_dst1), reinterpret_cast<float*>(src1), len, 1);
  bool sum_flag = true;
  for(int i=0 ; i < len; i++){
    if(!check_equal(*(src0+i), *(src1+i))){
      printf("cvt0 cvt1 sum is not equal in i:%d, naive cvt: %x, cvt1: %x\n", i, src0, src1);
      sum_flag = false;
      break;
    }
  }
  if(sum_flag){
    printf("cvt0 cvt1 sum is equal!\n");
  } else {
    printf("cvt0 cvt1 sum is not equal!\n");
  }
  free(src0);
  free(src1);
  free(cvt0_dst0);
  free(cvt0_dst1);
  free(cvt1_dst0);
  free(cvt1_dst1);
}

void test_sum(int len, int alignment){
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* src1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
    dst0[i] = 0x0bb;
    dst1[i] = 0x0bb;
  }
  bf16_sum_naive(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst0), &len);
  bf16_sum(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst1), &len, 0);

  bool sum_flag = true;
  for(int i=0; i < len; i++){
    if(*(dst0+i) != *(dst1+i)){
      sum_flag =  false;
      printf("bf16 sum diff, i: %d, naive sum: %x, sum: %x\n", i, *(dst0+i), *(dst1+i));
      break;
    }
  }
  if(sum_flag){
    printf("size: %d, bf16 sum is equal!\n", len);
  } else {
    printf("size: %d, bf16 sum is not equal!\n", len);
  }
  free(src0);
  free(src1);
  free(dst0);
  free(dst1);
}

double test_naive_sum_time(int len, int alignment) {
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
    dst0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  bf16_sum_naive(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst0), &len);
  tmp_time->stop();
  free(src0);
  free(dst0);
  return tmp_time->get_time();
}

double test_intrinsic_sum_time(int len, int type_flag, int alignment) {
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
    dst0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  if (type_flag == 2) {
    bf16_sum_naive(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst0), &len);
  } else {
    bf16_sum(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst0), &len, type_flag);
  }
  tmp_time->stop();
  free(src0);
  free(dst0);
  return tmp_time->get_time();
}

double test_FloatToBF16_time(int len, int type_flag, int alignment) {
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  FloatToBF16(reinterpret_cast<const float*>(src0), dst0, len, type_flag);
  tmp_time->stop();
  free(src0);
  free(dst0);
  return tmp_time->get_time();
}

double test_BF16ToFloat_time(int len, int type_flag, int alignment) {
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t), alignment));
  unsigned int* dst0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int), alignment));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa7bbb;
    src0[i] = rand();
  }
  utils::Time* tmp_time = new utils::Time();
  tmp_time->start();
  BF16ToFloat(reinterpret_cast<const uint16_t*>(src0), reinterpret_cast<float*>(dst0), len, type_flag);
  tmp_time->stop();
  free(src0);
  free(dst0);
  return tmp_time->get_time();
}

void test(int test_type, int alignment) {
  int len = 10000;
  for(len = 100; len< 10000000; len *= 10) {
      if ( test_type == 0) {
        // test fp32 to bf16
        test_f32Tob16(len, alignment);
      } else if (test_type == 1) {
        // test bf16 to fp32
        test_b16Tof32(len, alignment);
      } else if (test_type == 2) {
        // test bf16 sum
        test_sum(len, alignment);
      } else if (test_type == 3) {
        // test cvt0 cvt1 sum is equal or not
        test_cvt1_cvt2_sum_equal(len, alignment);
        return;
      }
      // test sum time
      std::vector<double> naive_times, intrinsic0_times;
      std::vector<double> intrinsic1_times;
      for(int i=0; i<105; i++){
        double naive_time = 0;
        double intrinsic0_time = 0;
        double intrinsic1_time = 0;
        if (test_type == 0) {
          naive_time = test_FloatToBF16_time(len, 2, alignment);
          intrinsic0_time = test_FloatToBF16_time(len, 0, alignment);
          intrinsic1_time = test_FloatToBF16_time(len, 1, alignment);
        } else if (test_type == 1) {
          naive_time = test_BF16ToFloat_time(len, 2, alignment);
          intrinsic0_time = test_BF16ToFloat_time(len, 0, alignment);
          intrinsic1_time = test_BF16ToFloat_time(len, 1, alignment);
        } else if (test_type == 2) {
          naive_time = test_intrinsic_sum_time(len, 2, alignment);
          intrinsic0_time = test_intrinsic_sum_time(len, 0, alignment);
          intrinsic1_time = test_intrinsic_sum_time(len, 1, alignment);
        }
        // the first 5 step for warmup
        if (i > 5) {
          naive_times.push_back(naive_time);
          intrinsic0_times.push_back(intrinsic0_time);
          intrinsic1_times.push_back(intrinsic1_time);
        }
      }
      float avg_naive_time = utils::average(naive_times);
      float avg_intrinsic0_time = utils::average(intrinsic0_times);
      float avg_intrinsic1_time = utils::average(intrinsic1_times);
      std::string op_type = "None";
      if (test_type == 0) {
        op_type = "float to bf16";
      } else if (test_type == 1) {
        op_type = "bf16 to float";
      } else if (test_type == 2) {
        op_type = "bf16 sum";
      }
      printf("alignment: %d %s time, size: %d, naive: %f us, intrinsic0: %f us, intrinsic1: %f us\n",
              alignment, op_type.c_str(), len, avg_naive_time, avg_intrinsic0_time, avg_intrinsic1_time);
  }
}

int main(){
  test(0, 64);
  test(1, 64);
  test(2, 64);
  test(3, 64);
  return 0;
}