#include <string>
#include <stack>
#include "../hot_100.h"

namespace hot_100
{

std::string decodeString(std::string s) {
    std::string result;
    int num = 0;
    std::stack<int> repeats;
    std::stack<std::string> repeat_contents;
    for (int i=0; i<s.length(); i++) {
        if (s[i] - '0' >=0 && s[i] - '0' <=9) {
            num = num * 10 + s[i] - '0';
        }
        else if ((s[i] >='a' && s[i] <='z') || (s[i] >='A' && s[i] <='Z')) {
            result += s[i];
        }
        else if (s[i]=='[') {
            repeats.push(num);
            num = 0;
            repeat_contents.push(result);
            result = "";
        }
        else if (s[i] == ']') {
            int num = repeats.top(); repeats.pop();
            std::string pre_str = repeat_contents.top(); repeat_contents.pop();
            while(num-- >0) {
                pre_str += result;
            }
            result = pre_str;
        }
    }
    return result;
}

} // namespace hot_100
