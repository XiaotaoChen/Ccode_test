#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

TreeNode* kthNode_dfs(TreeNode* root, int& k) {
    if (root==nullptr|| k==0) return nullptr;
    TreeNode* last = kthNode_dfs(root->left, k);
    if (last != nullptr) return last;
    k--;
    if (k==0) return root;
    return kthNode_dfs(root->right, k);
}


TreeNode* kthNode(TreeNode* root, int k) {
    return kthNode_dfs(root, k);
}

} // namespace sword_finger_offer
