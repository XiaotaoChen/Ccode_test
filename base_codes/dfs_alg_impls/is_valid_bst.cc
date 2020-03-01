#include <algorithm>

#include "../dfs_algs.h"

bool dfs::dfs_isValidBST(TreeNode* root, long min_val, long max_val) {
    if (root == nullptr) return true;
    if (root->val > min_val && root->val < max_val) {
        return dfs_isValidBST(root->left, min_val, root->val) && dfs_isValidBST(root->right, root->val, max_val);
    }
    else {
        return false;
    }
}

bool dfs::isValidBST(TreeNode* root) {
    return dfs_isValidBST(root, INT64_MIN, INT64_MAX);
}