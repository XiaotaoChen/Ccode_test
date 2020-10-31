#include <iostream>
#include <string>

#include "./base_class.h"

int main() {
    Child* chd = new Child();
    person* person = new Child();
    std::cout << "child pointer to show:\n";
    std::cout << "come from normal func: get_name: " << chd->get_name() << std::endl;
    std::cout << "come from virtual func: show: ";
    chd->show();
    std::cout << std::endl;

    std::cout << "person pointer to show:\n";
    std::cout << "come from normal func: get_name: " << person->get_name() << std::endl;
    std::cout << "come from virtual func: show: ";
    person->show();
    std::cout << std::endl;

    delete chd;
    delete person;
    
    return 0;
}