#include <immintrin.h>
#include <stdint.h>  // uint16_t
#include <stdlib.h>  // rand
#include <cstdio> // printf
#include <cmath> // fabs
#include <ctime>  // time

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

inline void convert_f32_to_b16(__m512i src, __m256i* dst)
{
  __m512i y = _mm512_bsrli_epi128(src, 2);
  *dst = _mm512_cvtepi32_epi16(y);
}

inline void convert_b16_to_f32(__m256i src, __m512i* dst)
{
  __m512i y = _mm512_cvtepu16_epi32(src);
  *dst = _mm512_bslli_epi128(y, 2);
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
 switch (type_flag)
 {
   case 0:
     {
       int i = 0;
       for(; i < (len / 16) * 16; i += 16){
         convert_b16_to_f32(*(__m256i*)(src+i), (__m512i*)(dst+i));
       }
       // process the remaining data
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       for(; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
   case 1:
     {
       int i = 0;
       for(; i < (len / 16) * 16; i += 16){
         convert_b16_to_f32(*(__m256i*)(src+i), (__m256i*)(dst+i), (__m256i*)(dst+i+8));
       }
       // process the remaining data
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       for(; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
   default:
     {
       unsigned int* dst_unsigned = reinterpret_cast<unsigned int*>(dst);
       for(int i=0; i < len; i++){
         *(dst_unsigned+i) = *(src+i)<<16;
       }
     }
     break;
 }
}

void FloatToBF16(const float* src, uint16_t* dst, int len, int type_flag){
 switch (type_flag)
 {
   case 0:
     {
       int i = 0;
       for(; i < (len / 16) * 16; i += 16){
         convert_f32_to_b16(*(__m512i*)(src+i), (__m256i*)(dst+i));
       }
       // process the remaining data
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       for(; i < len; i++){
         *(dst+i) = *(src_unsigned+i)>>16;
       }
     }
     break;
   case 1:
     {
       int i = 0;
       for(; i < (len / 16) * 16; i += 16){
         convert_f32_to_b16(*(__m256i*)(src+i), *(__m256i*)(src+i+8), (__m256i*)(dst+i));
       }
       // process the remaining data
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       for(; i < len; i++){
         *(dst+i) = *(src_unsigned+i)>>16;
       }
     }
     break;
   default:
     {
       const unsigned int* src_unsigned = reinterpret_cast<const unsigned int*>(src);
       for(int i=0; i < len; i++){
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

void bf16_sum(void* invec, void* inoutvec, int* len){
  int type_flag = 0;
  int i=0;
  int zero[8] = {0,0,0,0,0,0,0,0};
  __m256i zeros = *(__m256i*)zero;
  uint16_t* invec_16 = reinterpret_cast<uint16_t*>(invec);
  uint16_t* inoutvec_16 = reinterpret_cast<uint16_t*>(inoutvec);
  if(type_flag == 0){
    for(; i < (*len / 16) * 16; i += 16)
    {
      // convert in & inout to m512
      __m512i in_m512 = _mm512_bslli_epi128(_mm512_cvtepu16_epi32(*(__m256i*)(invec_16+i)), 2);
      __m512i out_m512 = _mm512_bslli_epi128(_mm512_cvtepu16_epi32(*(__m256i*)(inoutvec_16+i)), 2);
      // add them together to new_inout_m256
      __m512 newout_m512 = _mm512_add_ps((__m512)in_m512, (__m512)out_m512);
      // convert back and store in inout
      *(__m256i*)(inoutvec_16 + i) = _mm512_cvtepi32_epi16(_mm512_bsrli_epi128((__m512i)newout_m512, 2));
    }
  } else if(type_flag == 1){
//    int zero[8] = {0,0,0,0,0,0,0,0};
//    __m256i zeros = *(__m256i*)zero;
    for(; i< (*len / 16) * 16; i += 16){
      // convert in & out to m256
      __m256i invec0 = _mm256_unpacklo_epi16(zeros, *(__m256i*)(invec_16 + i));
      __m256i invec1 = _mm256_unpackhi_epi16(zeros, *(__m256i*)(invec_16 + i));
      __m256i outvec0 = _mm256_unpacklo_epi16(zeros, *(__m256i*)(inoutvec_16 + i));
      __m256i outvec1 = _mm256_unpackhi_epi16(zeros, *(__m256i*)(inoutvec_16 + i));
      // add them together to new_inout_m256
      __m256 new_inout0_m256 = _mm256_add_ps((__m256)invec0, (__m256)outvec0);
      __m256 new_inout1_m256 = _mm256_add_ps((__m256)invec1, (__m256)outvec1);
      // convert back and store in inout
      __m256i inout0_m256i = _mm256_srli_epi32((__m256i)new_inout0_m256, 16);
      __m256i inout1_m256i = _mm256_srli_epi32((__m256i)new_inout1_m256, 16);
      *(__m256i*)(inoutvec_16 + i) = _mm256_packus_epi32(inout0_m256i, inout1_m256i);
    }
  }
  // process the remaining data
  for(; i < *len; i++){
    unsigned int tmp_in = (*(invec_16 + i)) << 16;
    unsigned int tmp_out = (*(inoutvec_16 + i)) << 16;
    float in_float = *reinterpret_cast<float*>(&tmp_in);
    float inout_float = *reinterpret_cast<float*>(&tmp_out);
    inout_float += in_float;
    *(inoutvec_16 + i) = *reinterpret_cast<unsigned int*>(&inout_float)>>16;
  }
}

void bf16_sum_naive(void* invec, void* inoutvec, int* len){
  int i=0;
  // process the remaining data
  uint16_t* in_short = reinterpret_cast<uint16_t*>(invec);
  uint16_t* out_short = reinterpret_cast<uint16_t*>(inoutvec);
  for(; i < *len; i++){
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
    if(2*i%len == 0){
      printf("check f32 to b16, i; %d, fp32: %x, naive bf16: %x, bf16: %x\n", i, *(src+i), *(naive_cvt+i), *(intrinsics_cvt+i));
    }
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
    if(2*i%len == 0){
        printf("check b16 to f32, i; %d, bf16: %x, naive fp32: %x, fp32: %x\n", i, *(src+i), *(naive_cvt+i), *(intrinsics_cvt+i));
    }
  }
  return true;
}

void test_f32Tob16(int len){
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
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

void test_b16Tof32(int len){
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  unsigned int* dst0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  unsigned int* dst1 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
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

void test_cvt1_cvt2_sum_equal(int len){
  unsigned int* src0 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  unsigned int* src1 = reinterpret_cast<unsigned int*>(bf16_alloc(len*sizeof(unsigned int)));
  uint16_t* cvt0_dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* cvt0_dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* cvt1_dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* cvt1_dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
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
}

void test_sum(int len){
  uint16_t* src0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* src1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* dst0 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  uint16_t* dst1 = reinterpret_cast<uint16_t*>(bf16_alloc(len*sizeof(uint16_t)));
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
//    src0[i] = 0x7aaa;
    src0[i] = rand();
    dst0[i] = 0x0bb;
    dst1[i] = 0x0bb;
  }

  bf16_sum_naive(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst0), &len);
  bf16_sum(reinterpret_cast<void*>(src0), reinterpret_cast<void*>(dst1), &len);

  bool sum_flag = true;
  for(int i=0; i < len; i++){
    if(*(dst0+i) != *(dst1+i)){
      sum_flag =  false;
      break;
    }
    if(2*i % len == 0){
      printf("bf16 sum, i: %d, naive sum: %x, sum: %x\n", i, *(dst0+i), *(dst1+i));
    }
  }
  if(sum_flag){
    printf("bf16 sum is equal!\n");
  } else {
    printf("bf16 sum is not equal!\n");
  }
  free(src0);
  free(src1);
  free(dst0);
  free(dst1);
}

int main(){
  int len = 10000;
    for(len = 100; len< 10000000; len *= 10){
//      // test fp32 to bf16
//      test_f32Tob16(len);
//      // test bf16 to fp32
//      test_b16Tof32(len);
//      // test cvt0 cvt1 sum is equal or not
//      test_cvt1_cvt2_sum_equal(len);
      // test bf17=6 sum
      test_sum(len);
    }











}