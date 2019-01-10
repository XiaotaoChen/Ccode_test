#include <cstdio> // printf
#include "../utils/utils.h"

void mask_fp32(float* src, int size, int low_bits) {
 unsigned int mask_code = 0xffffffff;
 for(int i = 0; i < low_bits; i++) {
   mask_code &= ~(1U << i);
 }
 printf("mask code: %x\n", mask_code);
 unsigned int* p = reinterpret_cast<unsigned int*>(src);
 for(int i=0; i< size; i++, p+=1){
   *p = (*p) & mask_code;
 }
}

int main() {
  int len = 10;
  void* data = utils::alloc_mem(len * sizeof(float), 4);
  unsigned int* ui_ptr = reinterpret_cast<unsigned int*>(data);
  float* fp_ptr = reinterpret_cast<float*>(data);
//  utils::init_mem(data, len * sizeof(float));
  for(int i=0; i< len; i++) {
    fp_ptr[i] = i*0.0234353;
  }
  for(int i=0; i< len; i++){
    printf("i %d: %x, %f\n", i, ui_ptr[i], fp_ptr[i]);
  }
  mask_fp32(fp_ptr, len, 21);
  for(int i=0; i< len; i++){
    printf("i %d: %x, %f\n", i, ui_ptr[i], fp_ptr[i]);
  }
}