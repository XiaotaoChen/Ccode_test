#include <algorithm> // INT32_MIN
#include "../binary_search.h"

namespace binary_search {

// int dfs_max_path_sum(TreeNode* root, int& curr) {
//     if (root->left==nullptr && root->right==nullptr) {
//         curr = std::max(int(root->val), curr);
//         return root->val;
//     }
//     int left_max = INT32_MIN;
//     int right_max = INT32_MIN;
//     int max_path = int(root->val);
//     curr = std::max(curr, int(root->val));
//     if (root->left!=nullptr) {
//         left_max = dfs_max_path_sum(root->left, curr);
//         max_path = std::max(max_path, int(root->val)+left_max);
//         curr = std::max(curr, int(std::max(left_max, int(left_max+root->val))));
//     }
//     if (root->right!=nullptr) {
//         right_max = dfs_max_path_sum(root->right, curr);
//         max_path = std::max(max_path, int(root->val)+right_max);
//         curr = std::max(curr, int(std::max(right_max, int(right_max+root->val))));
//     }
//     if (root->left!=nullptr && root->right!=nullptr) {
//         curr = std::max(curr, int(left_max+right_max+root->val));
//     }

//     return max_path;
// }

int dfs_max_path_sum(TreeNode* root, int& curr) {
    if (root==nullptr) return 0;
    int left_max = dfs_max_path_sum(root->left, curr);
    int right_max = dfs_max_path_sum(root->right, curr);
    int max_path = int(root->val) + std::max(0, std::max(left_max, right_max));
    curr = std::max(curr, int(root->val) + std::max(0, left_max) + std::max(0, right_max));
    return max_path;
}

int maxPathSum(TreeNode* root) {
    int result = INT32_MIN;
    dfs_max_path_sum(root, result);
    return result;

}

}