#include<iostream>
#include<string>
#include <memory>

int main(){
    // std::string str="abcdefgh";
    // const char* ch_p = str.c_str();
    // const void* void_p = static_cast<const void*>(ch_p);
    // std::cout<<"str:"<<str<<std::endl;
    // std::cout<<"char*:"<<*(ch_p);
    // std::cout<<","<<*(ch_p+1)<<std::endl;
    // std::cout<<"void+1*:"<<static_cast<const char*>(void_p+1);
    // //std::cout<<","<<*(void_p+1)<<std::endl;

    int count = 10;
    int* ptr = new int[count];
    for (int i=0; i<count; i++) ptr[i] = i;
    std::shared_ptr<int> ptr1 = std::shared_ptr<int>(ptr);
    for (int i=0; i<count; i++) printf("%d ", *(ptr1.get()+i));
    printf("\n");
    std::shared_ptr<int> ptr2 = std::shared_ptr<int>(new int[10]);
    for (int i=0; i<count; i++) *(ptr2.get()+i) = i;

    for (int i=0; i<count; i++) printf("%d ", *(ptr2.get()+i));
    printf("\n");

    std::shared_ptr<int> ptr3 = ptr1;
    for (int i=0; i<count; i++) printf("%d ", *(ptr3.get()+i));
    printf("\n");

}
