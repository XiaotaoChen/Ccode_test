#include<cstdio>
#include<string>

#include "../search_algs.h"

std::string search::valid_string(std::string str) {
    int idx = 0;
    while(idx < str.length() && str[idx] == ' ') idx++;
    if (idx == str.length()) return "";
    // first char
    int begin_idx = idx;
    if (!(str[idx] == '-'|| str[idx] == '+' || (str[idx] >= '0' && str[idx] <= '9'))) return "";
    // followed char
    idx++;
    while(str[idx] >= '0' && str[idx] <= '9') idx++;
    if (idx -1 == begin_idx && (str[begin_idx] == '-' || str[begin_idx] == '+')) return "";
    return str.substr(begin_idx, idx - begin_idx);
}

int search::myAtoi(std::string str) {
    std::string valid_str = valid_string(str);
    if (valid_str == "") return 0;
    double result = 0;

    if (valid_str[0] !=  '-' && valid_str[0] != '+') {
        for (int i=0; i < valid_str.length(); i++) {
            result = result * 10 + (valid_str[i] - '0');
        }
        return result < INT32_MAX ? int(result) : INT32_MAX;
    } 
    else if (valid_str[0] == '-') {
        for (int i=1; i < valid_str.length(); i++) {
            result = result * 10 + (valid_str[i] - '0');
        }
        result = - result;
        return result > INT32_MIN ? result : INT32_MIN;
    }
    else if (valid_str[0] == '+') {
        for (int i=1; i < valid_str.length(); i++) {
            result = result * 10 + (valid_str[i] - '0');
        }
        return result < INT32_MAX ? int(result) : INT32_MAX;
    }
    return 0;
}