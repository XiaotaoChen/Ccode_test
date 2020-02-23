#include <cstdio>
#include <vector>

#include "../search_algs.h"


bool search::canReach(TreeNode* root, TreeNode* node) {
    if (root == nullptr || node == nullptr) return false;
    if (root->val == node->val) return true;
    return canReach(root->left, node) || canReach(root->right, node);
}

TreeNode* search::lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (canReach(root, p) && canReach(root, q)) {
        TreeNode* low_node = lowestCommonAncestor(root->left, p, q);
        if (low_node != nullptr) return low_node;
        low_node = lowestCommonAncestor(root->right, p, q);
        if (low_node != nullptr) return low_node;
        return root;
    }
    else {
        return nullptr;
    }
}

// TreeNode* search::lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
//     if (root == nullptr || root == p || root == q) return root;
//     TreeNode* left = lowestCommonAncestor2(root->left, p, q);
//     if (left == nullptr) return lowestCommonAncestor2(root->right, p, q);
//     else {
//         TreeNode* right = lowestCommonAncestor2(root->right, p, q);
//         if (right != nullptr) return root;
//         return right;
//     }
//     return nullptr;
// }

TreeNode* search::lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor2(root->left, p, q);
    TreeNode* right = lowestCommonAncestor2(root->right, p, q);

    if (left == nullptr && right == nullptr) return nullptr;
    else if (left != nullptr && right != nullptr) return root;
    else if (left == nullptr && right != nullptr) return right;
    else if (left != nullptr && right == nullptr) return left; 
    return nullptr;
}