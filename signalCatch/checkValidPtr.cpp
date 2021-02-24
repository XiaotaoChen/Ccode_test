#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "CException.h"

enum dtypes {_uint8, _int32, _float,};

static std::map<std::string, dtypes> dtype_map = {
    {"uint8", _uint8},
    {"int", _int32},
    {"float", _float},
};

// refer to: https://stackoverflow.com/questions/2350489/how-to-catch-segmentation-fault-in-linux
int isValidPtr(const void*p, int len) {
    if (!p) {
    return 0;
    }
    int ret = 1;
    int nullfd = open("/dev/random", O_WRONLY);
    if (write(nullfd, p, len) < 0) {
    ret = 0;
    /* Not OK */
    }
    close(nullfd);
    return ret;
}

int main()
{
    std::cout << "dtype_map: " << (typeid(dtype_map) == typeid(std::map<std::string, dtypes>)) << std::endl;
    for (const auto& item: dtype_map) {
        std::cout << item.first << ": " << item.second << std::endl;
    }

    std::map<std::string, dtypes>* ptr = &dtype_map;
    std::cout << "map ptr: " << ptr << std::endl;

    // destory map
    char* temp_str = "abcdefc";
    std::memcpy(ptr, temp_str, sizeof(temp_str));

    std::cout << "after changed *ptr: " << (typeid(*ptr) == typeid(std::map<std::string, dtypes>)) << std::endl;

    std::cout << "check valid ptr(10): " << isValidPtr(ptr, 10) << std::endl;
    std::cout << "check valid ptr(10000): " << isValidPtr(ptr, 10000) << std::endl;

    TRY
        for (const auto& item: *ptr) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    END_TRY

    return 0;
}

