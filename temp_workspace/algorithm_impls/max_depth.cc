#include <queue>
#include "../base_struct.h"
#include "../algorithms.h"

namespace algorithms
{

int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    std::queue<TreeNode*> qu;
    int depth = 0;
    qu.push(root);
    while(!qu.empty()) {
        depth++;
        int layer_size = qu.size();
        for (int i=0; i<layer_size; i++) {
            TreeNode* curr = qu.front(); qu.pop();
            if (curr->left!=nullptr) qu.push(curr->left);
            if (curr->right!=nullptr) qu.push(curr->right);
        }
    }
    return depth;
}

} // namespace algorithms
