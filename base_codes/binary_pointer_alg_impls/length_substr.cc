#include <string>
#include<algorithm>
#include <unordered_set>
#include "../binary_pointer.h"

int binary_pointer::lengthOfLongestSubstring(std::string s) {
    if (s.length()==0) return 0;
    std::unordered_set<char> set;
    int left=0;
    int result = 0;
    for (int i=0; i<s.length(); i++) {
        if (set.find(s[i])!=set.end()) {
            while(set.find(s[i])!=set.end()) {
                set.erase(s[left]);
                left++;
            }
        }
        set.insert(s[i]);
        result = std::max(result, i-left+1);
    }
    return result;
}
