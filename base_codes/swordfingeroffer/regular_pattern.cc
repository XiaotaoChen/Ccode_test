#include <string>
#include "../swordfingeroffer.h"


namespace sword_finger_offer
{

bool regular_pattern(std::string& str, std::string& pattern) {
    return match_core(str, 0, pattern, 0);
}

bool match_core(std::string& str, int index, std::string& pattern, int p_index) {
    if (index == str.length() && p_index == pattern.length()) return true;
    if (index == str.length() || p_index == pattern.length()) return false;
    if (p_index+1 < pattern.length() && pattern[p_index+1] == '*') {
        if (str[index] == pattern[p_index] || (str[index] == '.')) {
            return match_core(str, index+1, pattern, p_index) || match_core(str, index+1, pattern, p_index+2) || match_core(str, index, pattern, p_index+2);
        }
        else{
            return match_core(str, index, pattern, p_index+2);
        }
    }
    else {
        if (str[index] == pattern[p_index] || pattern[p_index] == '.'){
            return match_core(str, index+1, pattern, p_index + 1);
        }
        return false;
    }
}

} // namespace sword_finger_offer
