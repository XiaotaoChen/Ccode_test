#include "../data_structs/base_struct.h"
#include "../bfs_algs.h"

namespace bfs
{

bool is_mirror(TreeNode* root1, TreeNode* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 == nullptr) return false;
    if (root2 == nullptr) return false;
    if (root1->val != root2->val) return false;
    return is_mirror(root1->left, root2->right) && is_mirror(root1->right, root2->left);
}

bool isSymmetric_V2(TreeNode* root) {
    return is_mirror(root, root);
}

} // namespace bfs
