#include <algorithm>
#include "../data_structs/base_struct.h"
#include "../hot_100.h"

namespace hot_100
{

std::pair<int, int> rob_dfs(TreeNode* root) {
    if (root==nullptr) return {0, 0};
    std::pair<int, int> p_l = rob_dfs(root->left);
    std::pair<int, int> p_r = rob_dfs(root->right);
    int not_include = std::max(p_l.first, p_l.second) + std::max(p_r.first, p_r.second);
    int included = p_l.first + p_r.first + root->val;
    return {not_include, included};
}

int rob(TreeNode* root) {
    std::pair<int, int> pair = rob_dfs(root);
    return std::max(pair.first, pair.second);
}

} // namespace hot_100
