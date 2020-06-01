#include <queue>
#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int depthOfTreeNode(TreeNode* root) {
    if (root==nullptr) return 0;
    int left = depthOfTreeNode(root->left);
    int right = depthOfTreeNode(root->right);
    return left > right ? left+1 : right+1;
}

int depthOfTreeNode_v2(TreeNode* root) {
    if (root==nullptr)  return 0;
    std::queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    while(!q.empty()) {
        int size = q.size();
        depth++;
        for (int i=0; i<size; i++) {
            TreeNode* tmp = q.front(); q.pop();
            if (tmp->left !=nullptr) q.push(tmp->left);
            if (tmp->right != nullptr) q.push(tmp->right);
        }
    }
    return depth;
}

} // namespace sword_finger_offer
