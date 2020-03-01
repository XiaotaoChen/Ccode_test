#include <vector>
#include <queue>
#include <algorithm>
#include "../bfs_algs.h"


std::vector<std::vector<int>> bfs::zigzagLevelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (root == nullptr) return result;

    std::queue<TreeNode*> q;
    TreeNode* curr = root;
    q.push(curr);
    bool left_first = true;
    while(!q.empty()) {
        std::vector<int> tmp;
        std::vector<TreeNode*> curr_level;
        while(!q.empty()) {
            TreeNode* curr = q.front(); q.pop();
            tmp.push_back(curr->val);
            if (curr->left != nullptr) curr_level.push_back(curr->left);
            if (curr->right != nullptr) curr_level.push_back(curr->right);
        }
        if (!left_first) {
            std::reverse(tmp.begin(), tmp.end());
        }
        result.push_back(tmp);
        for (int i=0; i<curr_level.size(); i++) {
            q.push(curr_level[i]);
        }
        left_first = !left_first;
    }
    return result;
}
