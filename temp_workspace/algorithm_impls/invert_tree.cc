#include "../base_struct.h"
#include "../algorithms.h"

namespace algorithms
{

TreeNode* invertTree(TreeNode* root) {
    if (root==nullptr) return root;
    TreeNode* inverted_left = invertTree(root->left);
    TreeNode* inverted_right = invertTree(root->right);
    root->left = inverted_right;
    root->right = inverted_left;
    return root;
}

} // namespace algorithms
