#include<iostream>
#include<string>

int main(){
    std::string str="abcdefgh";
    const char* ch_p = str.c_str();
    const void* void_p = static_cast<const void*>(ch_p);
    std::cout<<"str:"<<str<<std::endl;
    std::cout<<"char*:"<<*(ch_p);
    std::cout<<","<<*(ch_p+1)<<std::endl;
    std::cout<<"void+1*:"<<static_cast<const char*>(void_p+1);
    //std::cout<<","<<*(void_p+1)<<std::endl;
    
}
