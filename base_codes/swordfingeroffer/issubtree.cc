#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool issametree(TreeNode* root1, TreeNode* root2) {
    if (root2 == nullptr) return true;
    if (root1 == nullptr) return false;
    if (int(root1->val) != int(root2->val)) return false;
    return issametree(root1->left, root2->left) && issametree(root1->right, root2->right);
}

bool issubtree(TreeNode* root1, TreeNode* root2) {
    if (root2 == nullptr) return true;
    if (root1 == nullptr) return false;

    if (root1->val != root2->val) return issubtree(root1->left, root2) || issubtree(root1->right, root2);
    return (issametree(root1->left, root2->left) && issametree(root1->right, root2->right)) || issubtree(root1->left, root2) || issubtree(root1->right, root2);
}

} // namespace sword_finger_offer
