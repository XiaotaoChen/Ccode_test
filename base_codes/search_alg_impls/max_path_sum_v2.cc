#include "../data_structs/base_struct.h"
#include "../search_algs.h"

namespace search
{

namespace binary_tree
{
    int maxPathSum_V2_dfs(TreeNode* root, int& curr_max) {
        if (root==nullptr) {
            return 0;
        }
        int left_path_val = maxPathSum_V2_dfs(root->left, curr_max);
        int right_path_val = maxPathSum_V2_dfs(root->right, curr_max);
        int max_val = root->val;
        if (left_path_val>0) max_val += left_path_val;
        if (right_path_val>0) max_val += right_path_val;
        if (max_val > curr_max) {
            curr_max = max_val;
        }
        return root->val + std::max(0,std::max(left_path_val, right_path_val));
    }

    int maxPathSum_V2(TreeNode *root) {
        int result = INT32_MIN;
        maxPathSum_V2_dfs(root, result);
        return result;
    }
} // namespace binary_tree


} // namespace search
