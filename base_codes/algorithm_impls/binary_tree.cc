#include <algorithm>  // min
#include <queue>
#include <stack>
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

void binary_tree::postorderTraversal(TreeNode *root, std::vector<int>& result) {
    if (root == NULL) return;
    if (root->left != NULL) {
        postorderTraversal(root->left, result);
    }
    if (root->right != NULL) {
        postorderTraversal(root->right, result);
    }
    result.push_back(root->val);
}

void binary_tree::postorderTraversalWithStack(TreeNode *root, std::vector<int>& result) {
    if (root == NULL) return ;
    std::stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()) {
        TreeNode* tmp = s.top();
        s.pop();
        result.push_back(tmp->val);
        if (tmp->left != NULL) s.push(tmp->left);
        if (tmp->right != NULL) s.push(tmp->right);
    }
    std::reverse(result.begin(), result.end());
    return;
}

int binary_tree::sumNumbers(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return root->val;
    queue<TreeNode*> qu;
    queue<int> node_number;
    qu.push(root);
    node_number.push(root->val);
    vector<int> leaf_number;

    while(!qu.empty()) {
        TreeNode* curr = qu.front();
        qu.pop();
        int curr_num = node_number.front();
        node_number.pop();
        if (curr->left == nullptr && curr->right == nullptr) {
            leaf_number.push_back(curr_num);
        }
        if (curr->left != nullptr) {
            qu.push(curr->left);
            node_number.push(curr_num * 10 + curr->left->val);
        }
        if (curr->right != nullptr) {
            qu.push(curr->right);
            node_number.push(curr_num * 10 + curr->right->val);
        }
    }

    // sum all leaf_number
    int sum = 0;
    for (int i=0; i < leaf_number.size(); i++) {
        sum += leaf_number[i];
    }
    return sum;
}