#include <stdint.h> //uint8_t
#include <limits> //numeric_limits
#include <cstdio> //printf
#include "../utils/utils.h" //alloc_mem(size_t size, int alignment);

using utils::alloc_mem;
using utils::free_mem;

void quantize(const float* src, uint8_t* dst, int len) {
  // dst size must be: len*sizeof(uint8_t) + 2*sizeof(float);
  float maximum = std::numeric_limits<float>::min();
  float minimum = std::numeric_limits<float>::max();
  for (int i = 0; i < len; i++) {
    maximum = src[i] > maximum ? src[i] : maximum;
    minimum = src[i] < minimum ? src[i] : minimum;
  }
  float max_dist = maximum - minimum;
  for (int i = 0; i < len; i++) {
    dst[i + 8] = (uint8_t)(255 * (src[i] - minimum) / max_dist);
  }
  float* fp_ptr = reinterpret_cast<float*>(dst);
  *fp_ptr = maximum;
  *(fp_ptr + 1) = minimum;

  printf("quantize max, min: %f, %f\n", maximum, minimum);
}

void dequantize(const uint8_t* src, float* dst, int len) {
  const float* fp_ptr = reinterpret_cast<const float*>(src);
  float maximum = *fp_ptr;
  float minimum = *(fp_ptr + 1);
  float max_dist = maximum - minimum;
  for(int i = 0; i < len; i++) {
    dst[i] = max_dist * src[i + 8] / 255 + minimum;
  }
}

void fp32_sum(float* invec, float* inoutvec, int* len) {
  for (int i = 0; i < *len; i++) inoutvec[i] += invec[i];
}

void quantize_sum(void* invec, void* inoutvec, int* len) {
  uint8_t* invec_ui_ptr = reinterpret_cast<uint8_t*>(invec);
  uint8_t* inoutvec_ui_ptr = reinterpret_cast<uint8_t*>(inoutvec);
  float* invec_fp = reinterpret_cast<float*>(alloc_mem(*len * sizeof(float), 4));
  float* inoutvec_fp = reinterpret_cast<float*>(alloc_mem(*len * sizeof(float), 4));

  // dequantize
  dequantize(invec_ui_ptr, invec_fp, *len);
  dequantize(inoutvec_ui_ptr, inoutvec_fp, *len);

  // do summation
  fp32_sum(invec_fp, inoutvec_fp, len);

  // quantize
  quantize(inoutvec_fp, inoutvec_ui_ptr, *len);

  free_mem(invec_fp);
  free_mem(inoutvec_fp);
}

void test_quantize(int len) {
  void* src = alloc_mem(len * sizeof(float), 4);
  void* quant_src = alloc_mem(len * sizeof(uint8_t) + 2 * sizeof(float), 4);
  void* dst = alloc_mem(len * sizeof(float), 4);

  float* fp_src = reinterpret_cast<float*>(src);
  uint8_t* ui_src = reinterpret_cast<uint8_t*>(quant_src);
  float* fp_dst = reinterpret_cast<float*>(dst);
  // init data
  for(int i = 0; i < len; i++) {
    fp_src[i] = 1.2443234 * i;
  }
  quantize(fp_src, ui_src, len);
  dequantize(ui_src, fp_dst, len);

  // print info
  float* fp_ui_src = reinterpret_cast<float*>(ui_src + len);
  float maximum = *fp_ui_src;
  float minimum = *(fp_ui_src + 1);
  printf("quantize maximum, minimum: %f, %f\n", maximum, minimum);
  for(int i=0; i < len; i++) {
    printf("src, quant, dst: %f, %d, %f\n", fp_src[i], ui_src[i], fp_dst[i]);
  }

  free_mem(src);
  free_mem(quant_src);
  free_mem(dst);
}

void test_quantize_sum(int len) {
  float* fp_src0 = reinterpret_cast<float*>(alloc_mem(len * sizeof(float), 4));
  float* fp_src1 = reinterpret_cast<float*>(alloc_mem(len * sizeof(float), 4));
  float* dequantized_dst = reinterpret_cast<float*>(alloc_mem(len * sizeof(float), 4));
  // init data
  for(int i = 0; i < len; i++) {
    fp_src0[i] = 1.002443234 * 10 / (i+1);
    fp_src1[i] = 0.00244 * (i + 1);
  }

  uint8_t* ui_src0 = reinterpret_cast<uint8_t*>(alloc_mem(len * sizeof(uint8_t) + 2 * sizeof(float), 4));
  uint8_t* ui_src1 = reinterpret_cast<uint8_t*>(alloc_mem(len * sizeof(uint8_t) + 2 * sizeof(float), 4));

  quantize(fp_src0, ui_src0, len);
  quantize(fp_src1, ui_src1, len);
  quantize_sum(ui_src0, ui_src1, &len);
  dequantize(ui_src1, dequantized_dst, len);

  // fp32 sum
  fp32_sum(fp_src0, fp_src1, &len);

  for(int i = 0; i < len; i++) {
    printf("i: %d sum fp32, quant: %f, %f\n", i, fp_src1[i], dequantized_dst[i]);
  }
}


int main() {
  int len = 10;
  test_quantize_sum(len);
  return 0;
}