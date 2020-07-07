#include<cstdio>
#include<vector>
#include<climits> // INT_MIN
// #include<algorithm> // max

#include "../search_algs.h"

int search::binary_tree::maxPathSum_dfs(TreeNode* root, int& result) {
    if (root == nullptr) return 0;
    int leftval = maxPathSum_dfs(root->left, result);
    int rightval = maxPathSum_dfs(root->right, result);
    int curr_max = root->val + std::max(leftval, 0) + std::max(rightval, 0);
    if (curr_max > result) result = curr_max;
    return root->val + std::max(leftval, std::max(rightval, 0));
}

int search::binary_tree::maxPathSum(TreeNode* root) {
    if (root == nullptr) return 0;
    int result = INT_MIN;
    maxPathSum_dfs(root, result);
    return result;
}
