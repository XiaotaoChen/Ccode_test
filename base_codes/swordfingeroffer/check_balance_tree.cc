#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::pair<bool, int> balance(TreeNode* root) {
    if (root==nullptr) {
        return std::make_pair(true, 0);
    }
    std::pair<bool, int> result = balance(root->left);
    if (!result.first) return result;
    int left_depth = result.second;
    result = balance(root->right);
    if (!result.first) return result;
    int right_depth = result.second;
    int diff = left_depth - right_depth;
    if (diff >=-1 && diff <=1) {
        return std::make_pair(true, left_depth > right_depth ? left_depth+1: right_depth+1);
    }
    return std::make_pair(false, 0);
}

bool check_balance_tree(TreeNode* root) {
    std::pair<bool, int> result = balance(root);
    return result.first;
}

} // namespace sword_finger_offer
