#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./singleton.h"
#include "./person.h"
#include "./person_interface.h"
/**
 * 1. 单例模式
*/
void test_singleton() {
    static singleton_imp::Singleton1* ins  = singleton_imp::Singleton1::getInstance();
    static singleton_imp::Singleton1* ins2  = singleton_imp::Singleton1::getInstance();
    printf("Singleton1 ins, ins2: %p, %p\n", ins, ins2);

    static singleton_imp::Singleton1_plus* s1_p_ins  = singleton_imp::Singleton1_plus::getInstance().get();
    static singleton_imp::Singleton1_plus* s1_p_ins2  = singleton_imp::Singleton1_plus::getInstance().get();
    printf("Singleton1_plus ins, ins2: %p, %p\n", s1_p_ins, s1_p_ins2);

    static singleton_imp::Singleton2* s2_ins  = singleton_imp::Singleton2::getInstance();
    static singleton_imp::Singleton2* s2_ins2  = singleton_imp::Singleton2::getInstance();
    printf("Singleton2 ins, ins2: %p, %p\n", s2_ins, s2_ins2);

    static singleton_imp::Singleton3* s3_ins  = singleton_imp::Singleton3::getInstance();
    static singleton_imp::Singleton3* s3_ins2  = singleton_imp::Singleton3::getInstance();
    printf("Singleton3 ins, ins2: %p, %p\n", s3_ins, s3_ins2);

    static singleton_imp::Singleton4* s4_ins  = singleton_imp::Singleton4::getInstance();
    static singleton_imp::Singleton4* s4_ins2  = singleton_imp::Singleton4::getInstance();
    printf("Singleton4 ins, ins2: %p, %p\n", s4_ins, s4_ins2);

    static person* per = singleton_imp::Singleton5<person>::getInstance();
    static person* per2 = singleton_imp::Singleton5<person>::getInstance();
    printf("template per: %p, per2: %p\n", per, per2);
    (*per).show(); (*per2).show();

}

void test_interface() {
    static personInterface* global_ins = personInterface::getInstance();
    std::cout << "person name: " << global_ins->get_name() << std::endl;
    std::cout << "person info: ";
    global_ins->show_info();
    std::cout << std::endl;
}

int main() {
    // test_singleton();
    test_interface();
}