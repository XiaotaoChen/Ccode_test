#include<iostream>
#include<typeinfo>
#include<string>
int main(){
    typedef float DType;
    DType a=1.2;
//    std::cout<<a<<", a.type: "<<std::to_string(DType)<<std::endl;
//    std::cout<<a<<", a.type: "<<typeid(a).name()<<std::endl;
    std::cout<<a<<", a.size: "<<sizeof(DType)<<std::endl;

    return 0;
}
