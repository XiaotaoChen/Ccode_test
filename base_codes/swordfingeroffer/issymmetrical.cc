#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool isSymmetrical(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 == nullptr || root2 == nullptr) return false;
    if (int(root1->val) != int(root2->val)) return false;
    return isSymmetrical(root1->left, root2->right) && isSymmetrical(root1->right, root2->left);
}

bool isSymmetrical(TreeNode* root) {
    return isSymmetrical(root, root);
}


} // namespace sword_finger_offer
