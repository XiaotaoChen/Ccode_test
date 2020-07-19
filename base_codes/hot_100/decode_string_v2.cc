#include <string>
#include "../hot_100.h"

namespace hot_100
{

std::string decodeString_dfs(std::string s, int& index) {
    int num=0;
    std::string res = "";
    while(index < s.length()) {
        if (s[index] >='0' && s[index] <='9') {
            num = num * 10 + s[index] - '0';
            index++;
        }
        else if (s[index] == '[') {
            std::string tmp = decodeString_dfs(s, ++index);
            while(num--> 0) {
                res += tmp;
            }
            num=0;
            index++;
        }
        else if (s[index] == ']') {
            break;
        }
        else {
            res += s[index];
            index++;
        }
    }
    return res;
}

std::string decodeString_V2(std::string s) {
    int index = 0;
    return decodeString_dfs(s, index);
}

} // namespace hot_100
