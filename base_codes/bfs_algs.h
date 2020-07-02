#ifndef BFS_ALG_
#define BFS_ALG_

#include <vector>
#include <string>
#include <map>
#include "data_structs/base_struct.h"

namespace bfs {

// https://leetcode-cn.com/problems/symmetric-tree/
bool isSymmetric(TreeNode* root);
bool isMirror(TreeNode* root1, TreeNode* root2);

bool isSymmetric_V2(TreeNode* root);

// https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/
std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root);

// https://leetcode-cn.com/problems/word-ladder/
int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);
bool is_one_diff(std::string str1, std::string str2);

// https://leetcode-cn.com/problems/word-ladder-ii/
std::vector<std::vector<std::string>> findLadders(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);
void dfs_find_ladders(std::vector<std::vector<std::string>>& combinations, std::vector<std::string> curr, std::vector<bool>& visited, std::vector<std::string>& wordList, std::string endword);
std::vector<std::vector<std::string>> findLadders_v2(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

std::vector<std::vector<std::string>> findLadders_v3(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);
void dfs_generate(std::vector<std::vector<std::string>>& combinations, std::string beginWord, std::string endWord, \
                  std::map<std::string, std::vector<std::string>>& path_map, std::vector<std::string> curr);

// https://leetcode-cn.com/problems/permutations/
void swap(int& a, int& b);
std::vector<std::vector<int>> permute(std::vector<int>& nums);
void dfs_permute(std::vector<std::vector<int>>& combinations, int depth, std::vector<int>& nums);

// https://leetcode-cn.com/problems/next-permutation/
void nextPermutation(std::vector<int>& nums);

// https://leetcode-cn.com/problems/combination-sum/
std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target);
void dfs_combinationsum(std::vector<std::vector<int>> & combinations, std::vector<int>& curr, std::vector<int>& candidates, int idx, int target);

}

#endif // BFS_ALG_