#include <cstdio>
#include <string>
#include "./move_rvalue_feature.h"


/**
 * 1. 类复制构造函数与move+右值引用。 右值主要是为了避免中间结果重复的拷贝，
 * 直接将对象的所有权交给目标，即修改所有权即可，而不需要拷贝新的。
 * 1. 注意person p1=person()使用构造函数赋值，person p1;p1=per;使用重载=赋值；
 * 2. 当不存在右值引用当构造函数时，而传入的是右值时，会将调原始的左值构造函数或重载
 * 3. std::move(per)后，最好不要访问per中的对象，因为其中的对象已经被move掉了。
*/
void test_move_feature(){
    using move_feature::person;
    person per("cxt", 12); // constructor with element
    person per2("cxt",13);
    person per_const(per); 
    person per_copy = per; // constructor with instance
    person p1;
    p1 = per; // copy assgin
    
    // when haven't define rvalue constructor it will call constructor with instance
    person per_const_rv(std::move(per)); 
    // when haven't define rvalue assign it will call copy assign
    person per_copy_rv;
    per_copy_rv = std::move(per2);
}

int main() {
    test_move_feature();
}