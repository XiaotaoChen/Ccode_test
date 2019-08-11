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
    std::string str1 = "minmax";
    std::string str2 = "minmax";
    if (str1 ==  str2) {
        printf("== it's equal, %s\n", str1.c_str());
    }
    if (strcmp(str1.c_str(), str2.c_str()) == 0) {
        printf("strcmp it's equal\n");
    }


    return 0;
}
