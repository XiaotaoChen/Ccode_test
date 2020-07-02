#include <vector>
#include <queue>
#include "../queue_algs.h"

namespace queue_alg
{
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (root == nullptr) return result;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        std::vector<int> tmp;
        for (int i=0; i<size; i++) {
            TreeNode* curr = q.front();q.pop();
            tmp.push_back(curr->val);
            if (curr->left!=nullptr) q.push(curr->left);
            if (curr->right!=nullptr) q.push(curr->right);
        }
        result.push_back(tmp);
    }
    return result;
}

} // namespace queue_alg
