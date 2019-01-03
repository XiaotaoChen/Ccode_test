#include<stdio.h>
#include<stdint.h>

void mask_fp32(float* fp, int size){
 uint16_t* p = reinterpret_cast<uint16_t*>(fp);
 for(int i=0; i< size; i++, p+=2){
   *p = 0;
 }
}

int main(){
  unsigned int a = 0x12345678;

  unsigned int b = a & 0xffff0000;
  printf("a: %d, %x, b: %d, %x\n", a, a, b, b);
  float fa = 1233214.5;
  float *fa_p;
   fa_p= &fa;
  unsigned int* fa_u = reinterpret_cast<unsigned int*>(fa_p) ;
  printf("fa: %f, fa_u: %d, %x \n", fa, *fa_u, *fa_u);
  unsigned int temp_b = *fa_u & 0xffff0000;
  printf("fa: %f, fa_u: %d, %x, b: %d, %x\n", fa, *fa_u, *fa_u, temp_b, temp_b);
  uint16_t* fa_s = reinterpret_cast<uint16_t*>(fa_p);
  *fa_s = 0;
  printf("fa: %f, fa_s: %d, %x \n", fa, *(fa_s+1), *(fa_s+1));
  uint16_t u_a = *fa_s;
  uint16_t u_b = *fa_s;
  if( u_a == u_b){
    printf("it's equal.\n");
  } else {
    printf("it's not equal.\n");
  }

  u_b += 1;
  if( u_a == u_b){
    printf("it's equal.\n");
  } else {
    printf("it's not equal.\n");
  }
  u_a = a>>16;
  printf("u_a: %x\n", u_a);


//  float fp[10]={100.1, 2.01, 13.001, 1.50001, 123.000001, 123.0000001, 0,0, 10, 99};
//  float fp[10];
//  for(int i=0;i <10;i++){
//    fp[i] =123.23456* i;
//  }
//  for(int i=0;i< 10; i++){
//    printf("i:%d, %f, %x \n", i, fp[i], fp[i]);
//  }
//  mask_fp32(fp, 10);
//  for(int i=0;i< 10; i++){
//    printf("i:%d, %f, %x \n", i, fp[i], fp[i]);
//  }


  return 0;
}