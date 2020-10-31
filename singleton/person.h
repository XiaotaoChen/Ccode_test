#ifndef PERSON_
#define PERSON_

#include <string>
#include <iostream>

class person {
public:
    person():name("cxt"),age(1){}
    ~person() {};
    person(std::string _name, int _age):name(_name), age(_age) {}
    std::string get_name() {
        return name;
    }
    
    void set_name(const std::string& name) {
        this->name = name;
    }

    int get_age() {
        return age;
    }

    void set_age(int age) {
        this->age = age;
    }

    void show() {
        std::cout << "name: " << name << ", age: " << age << std::endl;
    }

private:
    std::string name;
    int age;
};

#endif // PERSON_