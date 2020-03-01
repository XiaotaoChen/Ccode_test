#include "../bfs_algs.h"

bool bfs::isMirror(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 == nullptr || root2 == nullptr) return false;
    if (root1->val == root2->val) {
        return isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left);
    }
    return false;
}

bool bfs::isSymmetric(TreeNode* root) {
    return isMirror(root, root);
}