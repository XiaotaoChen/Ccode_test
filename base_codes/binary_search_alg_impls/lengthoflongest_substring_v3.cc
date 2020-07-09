#include <string>
#include <unordered_set>
#include "../binary_pointer.h"

namespace binary_pointer
{

int lengthOfLongestSubstring_v3(std::string s) {
    if (s.length()==0) return 0;
    if (s.length()==1) return 1;
    int begin = 0;
    int result = 1;
    std::unordered_set<char> ust;
    for (int i=0; i<s.length(); i++) {
        if (ust.find(s[i]) == ust.end()) {
            ust.insert(s[i]);
        }
        else {
            result = result > i-begin ? result : i - begin;
            while(ust.find(s[i])!=ust.end()) {
                ust.erase(s[begin]);
                begin++;
            }
            ust.insert(s[i]);
        }
    }
    result = result > s.length() - begin ? result : s.length() - begin;
    return result;
}

} // namespace binary_pointer
