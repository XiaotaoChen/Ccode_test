#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void bst2list(TreeNode* root, TreeNode** last) {
    if (root==nullptr) return;
    bst2list(root->left, last);
    root->left = *last;
    if ((*last) != nullptr) (*last)->right = root;
    *last = root;
    bst2list(root->right, last);
}

TreeNode* get_list_head(TreeNode* root) {
    TreeNode* head = root;
    while(head != nullptr && head->left != nullptr) head = head->left;
    return head;
}

} // namespace sword_finger_offer
