#include<stdio.h>
#include <cmath>

int main(){
  float a = 5.7;
  // float a_f = rintf(a);
  int8_t a_rf = static_cast<int8_t>(rintf(a));
  int8_t a_r = round(a);

  printf("a: %f, round(a): %d\n", a, a_r);
  printf("a: %f, static_cast<int8_t>(rintf(a)): %d\n", a, a_rf);

  return 0;
}