#include<stdio.h>

int main(){
  float a = 10;
  unsigned short b = *reinterpret_cast<unsigned int*>(&a)>>16;
  void* b_p;
  *(unsigned short*) b_p = *reinterpret_cast<unsigned int*>(&a)>>16; 
  printf("a: %f, %x \n b: %x \n", a, a, b);
  return 0;
}
