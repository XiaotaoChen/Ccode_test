#ifndef BINARY_POINTER_
#define BINARY_POINTER_

#include <string>

namespace binary_pointer
{

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters//
int lengthOfLongestSubstring(std::string s);

// https://leetcode-cn.com/problems/minimum-window-substring/
/*
    1. 将t放入map, init it to map[t[i]]  =1;
    2. left, right to record silde window. 
    if s[i] in map {
        map[s[i]]--;
        if(map[s[i]] <=0) match ++;
        if (match==map.size()) {
            
            increase left index util match < map.size() {
            record this substr;

            left++;
            }
        }
        
    }
*/

std::string minWindow(std::string s, std::string t);



} // namespace binary_pointer



#endif