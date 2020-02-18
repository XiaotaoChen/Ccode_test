#include<algorithm> // std::transform
#include "../search_algs.h"

bool search::is_char_num(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) return true;
    return false;
}

std::string search::keep_char_num(std::string str) {
    std::string result = "";
    for (int i=0; i<str.size(); i++) {
        if (is_char_num(str[i])) {
            result += str[i];
        }
    }
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool search::isPalindrome(std::string s) {
    std::string filted_str = keep_char_num(s);
    return filted_str == std::string(filted_str.rbegin(), filted_str.rend());
}

std::string search::longestPalindrome(std::string s) {
    if (s.length()<=1) return s;
    int p_len = 0;
    std::string curr_p;
    for (int i=1; i<=s.length(); i++) {
        for(int j=0; j< i - p_len; j++) {
            if (isPalindrome(s.substr(j, i -j))) {
                curr_p = s.substr(j, i -j);
                p_len = curr_p.length();
                break;
            }
        }
    }
    return curr_p;
}
