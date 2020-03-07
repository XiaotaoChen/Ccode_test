#ifndef BINARY_POINTER_
#define BINARY_POINTER_

#include <string>
#include <vector>
#include <unordered_map>

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

// https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/
/*
    1. 滑窗原理．因为words固定长度，但不知道开始的index在哪，故外层循环遍历i=0->word_len, 内层训练即可依次遍历　i+word_len, i + 2 * word_len进行滑窗．
*/

std::vector<int> findSubstring(std::string s, std::vector<std::string>& words);
bool is_ok(std::string s, int start, std::unordered_map<std::string, int> map, int word_len, int words_num);

std::vector<int> findSubstring_v2(std::string s, std::vector<std::string>& words);



} // namespace binary_pointer



#endif