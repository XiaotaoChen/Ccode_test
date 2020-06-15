#include <vector>
#include <string>
#include <map>
#include "../trace_back_algs.h"

namespace track_back 
{

void track_back_for_letter(std::vector<std::string>& combinations, std::string curr, std::string digits) {
    if (digits.length() == 0) {
        combinations.push_back(curr);
        return;
    }

    std::map<char, std::string> phone_map = {{'2', "abc"},
                                             {'3', "def"},
                                             {'4', "ghi"},
                                             {'5', "jkl"},
                                             {'6', "mno"},
                                             {'7', "pqrs"},
                                             {'8', "tuv"},
                                             {'9', "wxyz"}
                                             };
    std::string map_str = phone_map[digits[0]];
    for (int i=0; i<map_str.length(); i++) {
        track_back_for_letter(combinations, curr + map_str[i], digits.substr(1));
    }
}

std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> result;
    if (digits.length() == 0) return result;
    
    track_back_for_letter(result, "", digits);
    
    return result;
}


void track_back_for_letter_v2(std::vector<std::string>& combinations, std::string curr, std::string digits, int idx, std::map<char, std::string>& mp) {
    if (idx == digits.length()) {
        combinations.push_back(curr);
        return;
    }
    for (int i=0; i< mp[digits[idx]].length(); i++) {
        track_back_for_letter_v2(combinations, curr + mp[digits[idx]][i], digits, idx+1, mp);
    }
}

std::vector<std::string> letterCombinations_v2(std::string digits) {
    std::vector<std::string> result;
    if (digits.length() == 0) return result; 
    std::map<char, std::string> mp = {{'2', "abc"}, 
                                      {'3', "def"},
                                      {'4', "ghi"},
                                      {'5', "jkl"},
                                      {'6', "mno"},
                                      {'7', "pqrs"},
                                      {'8', "tuv"},
                                      {'9', "wxyz"},
                                      };
    track_back_for_letter_v2(result, "", digits, 0, mp);
    return result;
}


} // namespace track_back 

