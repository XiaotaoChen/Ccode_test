#include <vector>
#include <iostream>
#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::vector<std::vector<int>> sum_path(TreeNode* root, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> curr;
    if (root == nullptr) return result;
    sum_path_dfs(result, curr, root, target);
    return result;
}

void sum_path_dfs(std::vector<std::vector<int>>& commbinations, std::vector<int> curr, TreeNode* root, int target) {
    curr.push_back(root->val);
    target -= root->val;
    if (root->left == nullptr && root->right == nullptr) {
        if (target == 0) {
            commbinations.push_back(curr);
        }
        return;
    }
    if (target >= 0) {
        if (root->left!=nullptr) sum_path_dfs(commbinations, curr, root->left, target);
        if (root->right!=nullptr) sum_path_dfs(commbinations, curr, root->right, target);
    }
}


void sum_path_v2(TreeNode* root, int target) {
    std::vector<int> path;
    sum_path_dfs_v2(path, root, target);
}

void sum_path_dfs_v2(std::vector<int> curr, TreeNode* root, int target) {
    curr.push_back(root->val);
    target -= root->val;
    if (root->left == nullptr && root->right == nullptr) {
        if (target == 0) {
            for (auto& item: curr) std::cout << item << " ";
            std::cout << std::endl;
        }
    }
    if (target >= 0) {
        if (root->left!=nullptr) sum_path_dfs_v2(curr, root->left, target);
        if (root->right!=nullptr) sum_path_dfs_v2(curr, root->right, target);
    }
    curr.pop_back();
}

} // namespace name
