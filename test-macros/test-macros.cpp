#include<iostream>

int main(){
  int cpu=-1;
#if MASHDOW_USE_CUDA
  cpu=0;
#else
  cpu=1;
#endif
  std::cout<<"cpu: "<<cpu<<std::endl;
}
