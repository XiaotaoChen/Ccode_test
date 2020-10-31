#ifndef BASE_CLASS_
#define BASE_CLASS_

#include <iostream>
#include <string>

class person {
protected:
    std::string name;
    int age;

public:
    person():name("cxt"), age(1){}
    ~person(){}
    std::string get_name() {
        return "person_name: " + name;
    }
    virtual void show() {
        std::cout << "person info, name: " << name << ", age: " << age << std::endl;
    }

};

class Child: public person {
private:
    std::string child_sex;
public:
    ~Child(){}
    Child():person(),child_sex("man") {

    };
    std::string get_name() {
        return "child_name: " + name;
    };
    virtual void show() override {
        std::cout << "child name: " << name << ", age: " << age << ", sex: " << child_sex << std::endl;
    };
};


#endif // BASE_CLASS_