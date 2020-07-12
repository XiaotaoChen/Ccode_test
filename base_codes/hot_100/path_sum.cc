#include "../data_structs/base_struct.h"
#include "../hot_100.h"

namespace hot_100
{

void pathSum_dfs(TreeNode* root, int target, int& cnt) {
    if (root == nullptr) return ;
    if (target == root->val) cnt++;
    pathSum_dfs(root->left, target-root->val, cnt);
    pathSum_dfs(root->right, target-root->val, cnt);
}

void pathSum_first_dfs(TreeNode* root, int sum, int& cnt) {
    if (root == nullptr) return;
    pathSum_dfs(root, sum, cnt);
    pathSum_first_dfs(root->left, sum, cnt);
    pathSum_first_dfs(root->right, sum, cnt);
}



int pathSum(TreeNode* root, int sum) {
    if (root == nullptr) return 0;
    int cnt = 0;
    pathSum_first_dfs(root, sum, cnt);
    return cnt;
}

} // namespace hot_100

