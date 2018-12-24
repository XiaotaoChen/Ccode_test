#include<iostream>
#include<typeinfo>
#include<string>
#include<stdio.h>

void print_str(std::string name){
  printf("name: %s\n", name.c_str());
}
int main(){
    typedef float DType;
    DType a=1.2;
//    std::cout<<a<<", a.type: "<<std::to_string(DType)<<std::endl;
//    std::cout<<a<<", a.type: "<<typeid(a).name()<<std::endl;
    std::cout<<a<<", a.size: "<<sizeof(DType)<<std::endl;
    print_str("temp");

    return 0;
}
