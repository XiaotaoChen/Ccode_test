#include "../dfs_algs.h"


bool dfs::inorder_visit(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& pre) {
    if (root == nullptr) return false;
    bool flag = inorder_visit(root->left, first, second, pre);
    if (flag) return true;
    if (pre != nullptr && pre->val > root->val) {
        second = root;
        if (first == nullptr) {
            first = pre;
        }
        else {
            return true;
        }
    }
    pre = root;
    return inorder_visit(root->right, first, second, pre);
}

void dfs::recoverTree(TreeNode* root) {
    TreeNode *first = nullptr;
    TreeNode *second = nullptr;
    TreeNode *pre = nullptr;
    inorder_visit(root, first, second, pre);
    int tmp = first->val;
    first->val = second->val;
    second->val = tmp;
    return;
}