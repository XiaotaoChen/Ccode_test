#include "../binary_search.h"

void binary_search::dfs_bstToGst(TreeNode* root, TreeNode*& pre) {
    if (root==nullptr) return;
    if (root->right!=nullptr) dfs_bstToGst(root->right, pre);
    if (pre!=nullptr) {
        root->val += pre->val;
    }
    pre = root;
    if (root->left!=nullptr) dfs_bstToGst(root->left, pre);
}

TreeNode* binary_search::bstToGst(TreeNode* root) {
    TreeNode* pre = nullptr;
    dfs_bstToGst(root, pre);
    return root;
}