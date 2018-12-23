#include<iostream>
int main(){
  int a = 0xf0000000;
  std::cout<<"a: "<<std::dec<<a<<", hex a: "<<std::hex<<a<<std::endl;
  unsigned long long d = static_cast<long long>(a);
  std::cout<<"d: "<<std::dec<<d<<", hex d: "<<std::hex<<d<<std::endl;
  long long b = 0x8000000000000000;
  long long c = a & b;
  std::cout<<"c: "<<std::dec<<c<<", hex c: "<<std::hex<<c<<std::endl;
}
