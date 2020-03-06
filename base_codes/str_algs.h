#ifndef STRING_ALG_
#define STRING_ALG_

#include<string>
#include<vector>

namespace str_alg
{

// https://leetcode-cn.com/problems/longest-palindromic-substring/
std::string longestPalindrome(std::string s);

std::string longestPalindrome_dp(std::string s);

void swap(int*a, int* b);

void heap_modify(std::vector<int>& nums, int start, int end);

int heap_topk(std::vector<int>& nums, int k);


} // namespace str_alg

#endif