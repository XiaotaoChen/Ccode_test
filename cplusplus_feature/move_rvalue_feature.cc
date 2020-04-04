#include <string>
#include <cstdio>
#include <utility>
#include "./move_rvalue_feature.h"

namespace move_feature
{

    person::person(): name(""), age(-1) {}
    person::person(std::string name, int age): name(name), age(age) {
        printf("constructor with element\n");
    }
    person::~person() {}
    // 复制构造函数
    person::person(const person& other) {
        printf("constructor with instance\n");
        name = other.name;
        age = other.age;
    }
    person::person(person&& other) {
        printf("constructor with rvalue\n");
        name = std::move(other.name);
        age = other.age;
    }
    person& person::operator=(const person& other) {
        printf("copy assign\n");
        if (this == &other) return *this;
        name = other.name;
        age = other.age;
        return *this;
    }
    // 右值引用
    person& person::operator=(person&& other) {
        printf("rvalue assign\n");
        if (this == &other) return *this;
        name = std::move(other.name);
        age = other.age;
        return *this;
    }

} // namespace name