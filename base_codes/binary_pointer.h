#ifndef BINARY_POINTER_
#define BINARY_POINTER_

#include <string>
#include <vector>
#include <unordered_map>

namespace binary_pointer
{

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters//
int lengthOfLongestSubstring(std::string s);
int lengthOfLongestSubstring_v2(std::string s);
int lengthOfLongestSubstring_v3(std::string s);


// https://leetcode-cn.com/problems/minimum-window-substring/
std::string minWindow(std::string s, std::string t);
std::string minWindow_v2(std::string s, std::string t);
std::string minWindow_v3(std::string s, std::string t);

// https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/
std::vector<int> findSubstring(std::string s, std::vector<std::string>& words);
bool is_ok(std::string s, int start, std::unordered_map<std::string, int> map, int word_len, int words_num);

std::vector<int> findSubstring_v2(std::string s, std::vector<std::string>& words);

// https://leetcode-cn.com/problems/subarray-sum-equals-k/
int subarraySum(std::vector<int>& nums, int k);

// https://leetcode-cn.com/problems/merge-intervals/
std::vector<std::vector<int>> merge_intervals(std::vector<std::vector<int>>& intervals);

} // namespace binary_pointer



#endif