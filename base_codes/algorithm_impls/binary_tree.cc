#include <algorithm>  // min
#include <queue>
#include "../algorithm.h"

int binary_tree::minimum_depth_binary_tree(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL) return minimum_depth_binary_tree(root->right) + 1;
    else if (root->right == NULL) return minimum_depth_binary_tree(root->left) + 1;
    int left_high = minimum_depth_binary_tree(root->left) + 1;
    int right_high = minimum_depth_binary_tree(root->right) + 1;
    return std::min(left_high, right_high);
}

int binary_tree::minimum_depth_binary_tree_by_queue(TreeNode* root) {
    if (root == NULL) return 0;
    std::queue<TreeNode*> q;
    q.push(root);

    int depth = 1;
    while(!q.empty()) {
        int size = q.size();
        TreeNode* now;
        for (int i=0; i< size; i++) {
            now = q.front();
            if (now->left == NULL && now->right == NULL) return depth; 
            q.pop();
            if (now->left != NULL) q.push(now->left);
            if (now->right != NULL) q.push(now->right);
        }
        depth++;
    }
    return depth;
}


struct tree_depth {
    int depth;
    TreeNode* tree;
    tree_depth(int dep, TreeNode* tre): depth(dep), tree(tre){}
};
int binary_tree::minimum_depth_binary_tree_by_queue2(TreeNode* root) {
    if (root == NULL) return 0;
    std::queue<tree_depth> q;
    tree_depth root_depth = {1, root};
    q.push(root_depth);

    while(!q.empty()) {
        tree_depth now = q.front();
        if (now.tree->left == NULL && now.tree->right == NULL) return now.depth;
        q.pop();
        if (now.tree->left != NULL) q.push(tree_depth(now.depth + 1, now.tree->left));
        if (now.tree->right != NULL) q.push(tree_depth(now.depth + 1, now.tree->right));
    }
    return 0;
}