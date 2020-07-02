#include "../data_structs/base_struct.h"
#include "../dfs_algs.h"

namespace dfs
{

bool is_validBST_dfs(TreeNode* root, std::pair<int, int>& minmax) {
    if (root->left==nullptr) minmax.first = root->val;
    else {
        std::pair<int, int> lp;
        if (is_validBST_dfs(root->left, lp)) {
            if (root->val >lp.second) minmax.first = lp.first;
            else return false;
        }
        else return false;
    }

    if (root->right==nullptr) minmax.second=root->val;
    else {
        std::pair<int, int> rp;
        if (is_validBST_dfs(root->right, rp)) {
            if (root->val < rp.first) minmax.second = rp.second;
            else return false;
        }
        else return false;
    }
    return true;
}

bool isValidBST_V2(TreeNode* root) {
    if (root==nullptr) return true;
    std::pair<int,int> minmax;
    return is_validBST_dfs(root, minmax);
}

} // namespace dfs
