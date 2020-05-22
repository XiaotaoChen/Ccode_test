#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

namespace sword_finger_offer
{

bool comp(std::string& a, std::string& b) {
    std::string ab = a + b;
    std::string ba = b + a;
    return ab < ba; //升序
    // return ab > ba; // 降序
}

std::string mincombination(std::vector<int>& arr) {
    if (arr.size()==0) return "";
    if (arr.size()==1) return std::to_string(arr[0]);
    std::vector<std::string> strarr(arr.size());
    for (int i=0; i< arr.size(); i++) {
        strarr[i] = std::to_string(arr[i]);
    }
    std::sort(strarr.begin(), strarr.end(), comp);
    std::cout << std::endl;
    std::string result;
    for (std::string& item : strarr) {
        result = result + item;
    }
    return result;

}

} // namespace sword_finger_offer
