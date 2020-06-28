#ifndef DFS_ALGS_
#define DFS_ALGS_

#include <vector>
#include <string>

#include "data_structs/base_struct.h"

namespace dfs {

// https://leetcode-cn.com/problems/validate-binary-search-tree/
bool isValidBST(TreeNode* root);
bool dfs_isValidBST(TreeNode* root, long min_val, long max_val);

// https://leetcode-cn.com/problems/recover-binary-search-tree/
void recoverTree(TreeNode* root);
bool inorder_visit(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& pre);

// https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);
TreeNode* dfs_build_tree(std::vector<int>& preorder, std::vector<int>& inorder, int pre_start, int pre_end, int in_start, int in_end);

bool exist(std::vector<std::vector<char>>& board, std::string word);

}

#endif // DFS_ALGS_