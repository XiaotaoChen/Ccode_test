#ifndef TRACE_BACK_ALGS_
#define TRACE_BACK_ALGS_

#include <vector>
#include <string>

namespace track_back
{

// https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/comments/
std::vector<std::string> letterCombinations(std::string digits);
void track_back_for_letter(std::vector<std::string>& combinations, std::string curr, std::string digits);

// https://leetcode-cn.com/problems/generate-parentheses/comments/
std::vector<std::string> generateParenthesis(int n);
void track_back_generate_parenthesis(std::vector<std::string>& combinations, std::string curr, int left_count, int right_count, int n);

// https://leetcode-cn.com/problems/sudoku-solver/
void solveSudoku(std::vector<std::vector<char>>& board);
bool track_back_solveSudoku(std::vector<std::vector<char>>& board, int x, int y);
bool is_legal(std::vector<std::vector<char>>& board, int x, int y);

// https://leetcode-cn.com/problems/combination-sum-ii/
std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target);
void track_back_combination_sum(std::vector<std::vector<int>>& combinations, std::vector<int> curr, std::vector<int>& candidates, int index, int target);

} // namespace track_back


#endif // TRACE_BACK_ALGS_