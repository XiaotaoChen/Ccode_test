#include <vector>
#include <stack>
#include "../data_structs/base_struct.h"
#include "../stack_algs.h"

namespace stack_algs
{

std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) return result;
    TreeNode* ptr = root;
    std::stack<TreeNode*> st;

    while (!st.empty() || ptr) {
        while(ptr != nullptr) {
            st.push(ptr);
            ptr = ptr->left;
        }
        TreeNode* top = st.top(); st.pop();
        result.push_back(top->val);
        ptr = top->right;
    }
    return result;
}

} // namespace stack_algs
