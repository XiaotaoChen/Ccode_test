#include "../data_structs/base_struct.h"
#include "../dfs_algs.h"

namespace dfs
{

TreeNode* flatten_dfs(TreeNode* root, TreeNode*& ptr) {
    if (root->left == nullptr && root->right == nullptr) {
        ptr = root;
        return root;
    }
    TreeNode* left = root->left;
    TreeNode* right = root->right;
    root->left = nullptr;
    if (left !=nullptr) {
        root->right = flatten_dfs(left, ptr);
    }
    else {
        ptr = root;
    }

    if (right != nullptr) {
        TreeNode* last_node = ptr;
        last_node->right = flatten_dfs(right, ptr);
    }
    return root;
}

void flatten(TreeNode* root) {
    if (root==nullptr) return;
    TreeNode* last_node = nullptr;
    flatten_dfs(root, last_node);
}

void flatten_V2(TreeNode* root) {
    if (root==nullptr) return;
    flatten_V2(root->left);
    flatten_V2(root->right);
    if (root->left != nullptr) {
        TreeNode* last = root->left;
        while(last->right!=nullptr)  last=last->right;
        last->right = root->right;
        root->right = root->left;
        root->left=nullptr;
    }
    return;
}

void flatten_V3(TreeNode* root) {
    if (root == nullptr) return;
    TreeNode* curr = root;
    while(curr!=nullptr) {
        if (curr->left != nullptr) {
            TreeNode* last = curr->left;
            while(last->right!=nullptr) last = last->right;
            last->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}


} // namespace dfs
