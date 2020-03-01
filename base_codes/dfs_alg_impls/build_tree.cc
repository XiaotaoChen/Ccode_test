#include<vector>

#include "../dfs_algs.h"

TreeNode* dfs::dfs_build_tree(std::vector<int>& preorder, std::vector<int>& inorder, int pre_start, int pre_end, int in_start, int in_end) {
    if (pre_start == pre_end) {
        TreeNode* tmp = new TreeNode(preorder[pre_start]);
        return tmp;
    }
    int mid_val = preorder[pre_start];
    int in_idx = -1;
    for (int i=in_start; i<=in_end; i++) {
        if (inorder[i] == mid_val) {
            in_idx = i;
            break;
        }
    }
    int left_count = in_idx - in_start;
    int right_count = in_end - in_start - left_count;
    TreeNode* root = new TreeNode(mid_val);
    if (left_count > 0){
        root->left = dfs_build_tree(preorder, inorder, pre_start+1, pre_start+left_count, in_start, in_idx -1);
    }
    if (right_count >0){
        root->right = dfs_build_tree(preorder, inorder, pre_start+left_count + 1, pre_end, in_idx+1, in_end);
    }
    
    return root;
}

TreeNode* dfs::buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
    if (preorder.size() ==0) return nullptr;
    TreeNode* root = dfs_build_tree(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
    return root;
}