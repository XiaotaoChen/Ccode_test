#ifndef MOVE_FEATURE
#define MOVE_FEATURE

#include <string>
#include <cstdio>
#include <utility>

namespace move_feature
{

class person {
public:
    person();
    ~person();
    person(std::string name, int age);
    // 复制构造函数
    person(const person& other);
    person(person&& other);
    person& operator=(const person& other);
    person& operator=(person&& other);
private:
    std::string name;
    int age;
};


} // namespace name

#endif