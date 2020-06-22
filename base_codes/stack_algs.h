#ifndef STACK_ALGS_
#define STACK_ALGS_

#include <vector>
#include <string>

namespace stack_algs {

// https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/
int evalRPN(std::vector<std::string>& tokens);
int strToint(std::string str);
int op_maps(int a, int b, char op_type);

// https://leetcode-cn.com/problems/trapping-rain-water/
int trap(std::vector<int>& height);
int trap_v2(std::vector<int>& height);

// https://leetcode-cn.com/problems/longest-valid-parentheses/
int longestValidParentheses(std::string s);
int longestValidParentheses_v2(std::string s);

int longestValidParentheses_v3(std::string s);

std::string simplepath(std::string& path);

// https://leetcode-cn.com/problems/valid-parentheses/
bool isValid_parentness(std::string& s);

}

#endif