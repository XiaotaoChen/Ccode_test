#include <cstdio>
#include "../binary_search.h"

void binary_search::dfs_binode(TreeNode* root, TreeNode*& pre) {
    if (root==nullptr) return;
    if (root->left!=nullptr) {
        dfs_binode(root->left, pre);
    }
    pre->right = root;
    root->left = nullptr;
    pre = root;
    if (root->right!=nullptr) {
        dfs_binode(root->right, pre);
    }
}



TreeNode* binary_search::convertBiNode(TreeNode* root){
    TreeNode* head = new TreeNode(-1);
    TreeNode* pre = head;
    dfs_binode(root, pre);
    TreeNode* new_root = head->right;
    delete head;
    return new_root;
}