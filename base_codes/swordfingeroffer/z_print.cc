#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void print_binary_tree_with_z(TreeNode* root){
    if (root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    int lines = 0;

    while(!q.empty()) {
        std::vector<int> layer;
        int size = q.size();
        layer.reserve(size);
        for (int i=0; i<size; i++) {
            TreeNode* tmp_node = q.front();q.pop();
            layer.push_back(tmp_node->val);
            if (tmp_node->left != nullptr) q.push(tmp_node->left);
            if (tmp_node->right != nullptr) q.push(tmp_node->right);
        }
        if (lines == 1) {
            for (auto iter=layer.rbegin(); iter != layer.rend(); iter++) 
                std::cout << *iter << " ";
        }
        else{
            for (auto iter=layer.begin(); iter != layer.end(); iter++) 
                std::cout << *iter << " ";
        }
        std::cout << std::endl;
        lines = 1 - lines;
    }
}

void print_binary_tree_with_z_v2(TreeNode* root) {
    if (root==nullptr) return ;
    std::stack<TreeNode*> st[2];
    int lines=0;
    st[lines].push(root);
    while(!st[lines].empty()) {
        int reverse = 1 - lines;
        while(!st[lines].empty()) {
            TreeNode* tmp = st[lines].top(); st[lines].pop();
            std::cout << tmp->val << " ";
            if (lines == 0) {
                if (tmp->left != nullptr) st[reverse].push(tmp->left);
                if (tmp->right != nullptr) st[reverse].push(tmp->right);
            }
            else {
                if (tmp->right != nullptr) st[reverse].push(tmp->right);
                if (tmp->left != nullptr) st[reverse].push(tmp->left);
            }
        }
        std::cout << std::endl;
        lines = reverse;
    }
}

} // namespace sword_finger_offer
