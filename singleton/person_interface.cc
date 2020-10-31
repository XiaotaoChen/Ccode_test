#include <string>
#include <memory>

#include "./person_interface.h"

class personInstance: public personInterface {
private:
    std::shared_ptr<person> global_ins;

public:
    personInstance(std::string& name, int age) {
        global_ins.reset(new person(name, age));
    }
    ~personInstance() {}

    virtual std::string get_name() override {
        return global_ins->get_name();
    }
    virtual void show_info() override {
        global_ins->show();
    }
};

personInterface* personInterface::getInstance() {
    std::string name = "cxt";
    int age = 1;
    return new personInstance(name, age);
}