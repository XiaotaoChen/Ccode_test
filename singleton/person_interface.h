#ifndef PERSON_INTERFACE_
#define PERSON_INTERFACE_

#include <string>

#include "./person.h"


class personInterface {

public:
    // 单例模式
    static personInterface* getInstance();
    // 析构函数要定义成虚函数
    virtual ~personInterface(){}
    // 纯虚函是
    virtual std::string get_name()=0;
    virtual void show_info()=0;
};


#endif // PERSON_INTERFACE_