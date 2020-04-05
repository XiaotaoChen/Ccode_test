#ifndef SINGLETON_
#define SINGLETON_

#include <pthread.h> // pthread mutex
#include <memory> // shared_ptr
#include "./move_rvalue_feature.h"

namespace singleton_imp
{

// 1. 懒汉式
class Singleton1 {
public:
    static Singleton1* getInstance() {
        if(my_singleton==nullptr) {
            my_singleton = new Singleton1();
        }
        return my_singleton;
    }

private:
    static Singleton1* my_singleton;
    Singleton1(){};
    Singleton1(const Singleton1& other);
    ~Singleton1(){};
};
// 初始化　静态变量
Singleton1* Singleton1::my_singleton = nullptr;

// 避免内存泄漏, 使用shared_ptr, 该种情况下析构函数必须为public, 供shared ptr的类调用 (计数器只能在构造函数为public情况下存在多个实例的时候用．)
class Singleton1_plus {
public:
    static std::shared_ptr<Singleton1_plus> getInstance() {
        if(my_singleton==nullptr) {
            my_singleton.reset(new Singleton1_plus());
        }
        return my_singleton;
    }
    ~Singleton1_plus(){};

private:
    static std::shared_ptr<Singleton1_plus> my_singleton;
    Singleton1_plus(){};
    Singleton1_plus(const Singleton1& other);
};

std::shared_ptr<Singleton1_plus> Singleton1_plus::my_singleton = nullptr;

// 2. 懒汉式保证线程安全
class Singleton2 {
public:
    static Singleton2* getInstance() {
        if (my_singleton==nullptr) {
            pthread_mutex_lock(&mutex);
            if (my_singleton==nullptr) { // 加双重判断是为了避免thread1在等待锁，而thread2 new完后释放锁，此时thread1不应该再new了．
                my_singleton = new Singleton2();
            }
            pthread_mutex_unlock(&mutex);
        }
        return my_singleton;
    }

private:
    static Singleton2* my_singleton;
    static pthread_mutex_t mutex;
    Singleton2(){}
    Singleton2(const Singleton2& other);
    ~Singleton2(){}
};
// init, 要初始化ｍｕｔｅｘ
Singleton2* Singleton2::my_singleton = nullptr;
pthread_mutex_t Singleton2::mutex = PTHREAD_MUTEX_INITIALIZER;


// 3. 饿汉式，程序运行时就被初始化，即把指针换成对象
class Singleton3{
public:
    static Singleton3* getInstance() {
        return &my_singleton;
    }

private:
    static Singleton3 my_singleton;
    Singleton3(){};
    Singleton3(const Singleton3& other);
    ~Singleton3(){};
};
// 初始化
Singleton3 Singleton3::my_singleton;


// ４.使用局部静态变量,其本身保证了线程安全, 由于没有静态成员变量，故不需要初始化
class Singleton4 {
public:
    static Singleton4* getInstance() {
        static Singleton4 my_signleton;
        return &my_signleton;
    }

private:
    Singleton4(){}
    Singleton4(const Singleton4& other);
    ~Singleton4(){}

};

// 5. 包装单例
template<typename T>
class Singleton5
{
private:
    Singleton5(){}
    Singleton5(const Singleton5& other);
    ~Singleton5(){}
public:
    static T* getInstance() {
        static T m_instance = T("cxt", 12);
        return &m_instance;
    }
};


} // namespace singleton_imp


#endif