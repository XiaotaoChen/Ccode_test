#include <vector>
#include "../data_structs/base_struct.h"
#include "../dfs_algs.h"

namespace dfs
{

TreeNode* buildTree_dfs_V2(std::vector<int>& preorder, std::vector<int>& inorder, int pre_left, int pre_right, int in_left, int in_right) {
    int val = preorder[pre_left];
    TreeNode* root = new TreeNode(val);
    if (pre_left == pre_right) return root;
    
    int mid_idx;
    for (mid_idx = in_left; mid_idx<=in_right; mid_idx++) {
        if (inorder[mid_idx]==val) break;
    }
    int left_tree_size = mid_idx - in_left;
    int right_tree_size = in_right - mid_idx;
    if (left_tree_size > 0) root->left = buildTree_dfs_V2(preorder, inorder, pre_left+1, pre_left+left_tree_size, in_left, mid_idx-1);
    if (right_tree_size > 0) root->right = buildTree_dfs_V2(preorder, inorder, pre_left+left_tree_size+1, pre_right, mid_idx+1, in_right);
    return root;
}

TreeNode* buildTree_V2(std::vector<int>& preorder, std::vector<int>& inorder) {
    if (preorder.size()==0) return nullptr;
    return buildTree_dfs_V2(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
}

} // namespace dfs
