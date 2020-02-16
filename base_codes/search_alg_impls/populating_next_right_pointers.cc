#include<cstdio>
#include<vector>
#include<queue>

#include "../search_algs.h"


void search::populating_next_right_pointers_in_each_node(TreeLinkNode *root) {
    if (root == nullptr) return ;

    TreeLinkNode* curr = root;
    std::queue<TreeLinkNode*>  q;
    
    q.push(curr);
    while(!q.empty()) {
        std::vector<TreeLinkNode*> layers;
        while(!q.empty()) {
            TreeLinkNode* tmp = q.front();
            q.pop();
            layers.push_back(tmp);
        }
        if (layers.size() >= 1) {
            TreeLinkNode* curr_head = layers[0];
            if (curr_head->left != nullptr) q.push(curr_head->left);
            if (curr_head->right != nullptr) q.push(curr_head->right);

            // curr_head->next = curr_head->right;
            // curr_head = curr_head->right;
            
            for(int i=1; i< layers.size(); i++) {
                // collect next node
                if (layers[i]->left != nullptr) q.push(layers[i]->left);
                if (layers[i]->right != nullptr) q.push(layers[i]->right);
                // setting next pointer to the right pointer;
                curr_head->next = layers[i];
                curr_head = layers[i];
            }
        }
    }
}