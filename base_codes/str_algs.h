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

// https://leetcode-cn.com/problems/multiply-strings/
std::string multiply(std::string num1, std::string num2);


} // namespace str_alg

#endif