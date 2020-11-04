#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
};

int main() {
    Person* p1 = new Person();
    p1->name = "cxt";
    p1->age = 18;

    std::cout << "name: " << p1->name << ", age: " << p1->age << std::endl;

    void* ptr = reinterpret_cast<void*>(p1);

    Person* p2 = reinterpret_cast<Person*>(ptr);

    std::cout << "name: " << p2->name << ", age: " << p2->age << std::endl;

    std::cout << "address p1: " << p1 << ", void ptr: " << ptr << ", p2: " << p2 << std::endl;
    std::cout << "sizeof(p1): " << sizeof(p1) << ", sizeof(ptr): " << sizeof(ptr) << ", sizeof(p2): " << sizeof(p2) << std::endl;


    std::cout << "sizeof(long): " << sizeof(long) << ", sizeof(long long): " << sizeof(long long) << std::endl;

    long long addr = reinterpret_cast<long long>(p1);
    std::cout << "long type addr: " << addr << ", "<< std::hex << addr << std::dec << std::endl;
    Person* p3 = reinterpret_cast<Person*>(addr);
    std::cout << "name: " << p3->name << ", age: " << p3->age << std::endl;

    return 0;
}