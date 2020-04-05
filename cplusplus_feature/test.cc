#include <cstdio>
#include <string>
#include <vector>
#include "./move_rvalue_feature.h"
#include "./singleton.h"

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

/**
 * 2. vector中emplace_back与push_back的区别．emplace_back是转移语义．push_back会创建临时对象
 * 1. 注意vector本身的扩容机制，capacity满了，会调用复制构造函数把原始容器内容拷贝到新空间．最好只push 一个数据到vector中看现象
 * 2. emplace_back原地构造对象，相对于push back避免了第二次的拷贝．当emplace_back传入左值或右值对象时，现象与push back相同．
 * 绝大部分情况下emplace back可以替换push back, 除了奇葩的例子如：https://stackoverrun.com/cn/q/6037224
*/
void test_emplace_back() {
    std::vector<move_feature::person> vect1;
    // move_feature::person per("cxt", 12);
    vect1.push_back({"cxt", 13}); // 构建person对象，然后因为是右值，会调用转移构造函数
    // vect1.push_back(move_feature::person("cxt", 14)); // １. 传入参数本身构建函数，２．右值调用转移函数, 于上面行为相同
    // vect1.push_back(per); // 这里会调用１次复制构造函数

    std::vector<move_feature::person> vect2;
    vect2.emplace_back("cxt", 13);
    // vect2.emplace_back(move_feature::person("cxt", 14));
    // vect2.emplace_back(per);
}

/**
 * 3. 单例模式
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

    static move_feature::person* per = singleton_imp::Singleton5<move_feature::person>::getInstance();
    static move_feature::person* per2 = singleton_imp::Singleton5<move_feature::person>::getInstance();
    printf("template per: %p, per2: %p\n", per, per2);
    (*per).show(); (*per2).show();

}


int main() {
    // test_move_feature();
    // test_emplace_back();
    test_singleton();
}