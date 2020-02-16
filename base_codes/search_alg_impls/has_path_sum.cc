#include<cstdio>
#include<vector>
#include<queue>

#include "../search_algs.h"

bool search::hasPathSum(TreeNode *root, int sum) {
    if (root == nullptr) return false;
    std::queue<TreeNode*> q1;
    std::queue<int> sums;
    q1.push(root);
    sums.push(root->val);
    while(!q1.empty()) {
        TreeNode* curr = q1.front();
        int curr_sum = sums.front();
        q1.pop(); sums.pop();

        if (curr->left == nullptr && curr->right == nullptr && curr_sum == sum) return true;
        if (curr->left != nullptr) {
            q1.push(curr->left); sums.push(curr_sum + curr->left->val);
        }
        if (curr->right != nullptr) {
            q1.push(curr->right); sums.push(curr_sum + curr->right->val);
        }
    }
    return false;
}


// this may out of memory limits
std::vector<std::vector<int>> search::pathSum(TreeNode *root, int sum) {
    std::vector<std::vector<int>> results;
    if (root == nullptr) return results;
    std::queue<TreeNode*> q1;
    std::queue<int> sums;
    std::queue<std::vector<int>> curr_paths;
    q1.push(root);
    sums.push(root->val);
    std::vector<int> tmp(1, root->val);
    curr_paths.push(tmp);
    while(!q1.empty()) {
        TreeNode* curr = q1.front();
        int curr_sum = sums.front();
        std::vector<int> curr_path = curr_paths.front();
        q1.pop(); sums.pop(); curr_paths.pop();

        if (curr->left == nullptr && curr->right == nullptr && curr_sum == sum){
            results.push_back(curr_path);
        }
        if (curr->left != nullptr) {
            q1.push(curr->left); sums.push(curr_sum + curr->left->val);
            std::vector<int> tmp2(curr_path);
            tmp2.push_back(curr->left->val);
            curr_paths.push(tmp2);
        }
        if (curr->right != nullptr) {
            q1.push(curr->right); sums.push(curr_sum + curr->right->val);
            std::vector<int> tmp3(curr_path);
            tmp3.push_back(curr->right->val);
            curr_paths.push(tmp3);
        }
    }
    return results;
}

std::vector<std::vector<int>> search::pathSum_bfs(TreeNode *root, int sum) {
    std::vector<std::vector<int>> results;
    if (root == nullptr) return results;
    std::vector<int> v;
    pathSum_aux(root, sum, v, results);
    return results;
}

void search::pathSum_aux(TreeNode *root, int res,  std::vector<int> v, std::vector<std::vector<int>> &results) {
    if (root == nullptr) return;
    // if (root->val > res) return;
    v.push_back(root->val);
    if (root->left==nullptr && root->right == nullptr && root->val == res) {
        results.push_back(v);
    }
    pathSum_aux(root->left, res - root->val, v, results);
    pathSum_aux(root->right, res - root->val, v, results);
}