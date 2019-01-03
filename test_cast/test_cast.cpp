#include<stdio.h>

int main(){
  int a = 10;
  int* a_p;
  *a_p = a;
//  a_p = &a;
  float a_f = static_cast<float>(a);
//  float a_rf = reinterpret_cast<float>(a);
  double a_d = static_cast<double>(a);
//  double a_rd = reinterpret_cast<double>(a);
  printf("a: %d(dec), %x(hex), %f(static_cast), %x, %lf(static_cast), %x\n",
         a, a, a_f, a_f, a_d, a_d);

  float* a_f_p;
  a_f_p = reinterpret_cast<float*>(&a);
//  a_f_p = reinterpret_cast<float*>(a_p);
  printf("a_f_p:%x, %f\n", *a_f_p, *a_f_p);

  return 0;
}