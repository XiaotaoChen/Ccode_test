#include <vector>
#include "../line_tree_algs.h"


namespace line_tree_alg
{
   
void NumArray_v3::create_line_tree(std::vector<int>& nums, SegNode*& root, int left, int right) {
    root = new SegNode();
    if (left == right) {
        root->sum = nums[left];
        root->begin = root->end = left;
        return;
    }
    int mid = (left + right)/2;
    create_line_tree(nums, root->left, left, mid);
    create_line_tree(nums, root->right, mid+1, right);
    root->begin = left;
    root->end = right;
    root->sum = root->left->sum + root->right->sum;
}

void NumArray_v3::update_line_tree(SegNode* root, int idx, int val) {
    if (root->left==root->right){
        root->sum = val;
        return;
    }
    int mid = (root->begin + root->end) /2;
    if (idx <=mid) update_line_tree(root->left, idx, val);
    else update_line_tree(root->right, idx, val);
    root->sum = root->left->sum + root->right->sum;
}

int NumArray_v3::sum_range_line_tree(SegNode* root, int left, int right) {
    if (left<=root->begin && right>=root->end) {
        return root->sum;
    }
    int mid = (root->begin + root->end) /2;
    int ans = 0;
    if (left<=mid) {
        ans += sum_range_line_tree(root->left, left, right);
    }
    if (right > mid) {
        ans += sum_range_line_tree(root->right, left, right);
    }
    return ans;
}

NumArray_v3::NumArray_v3(std::vector<int>& nums): nums(&nums), n(nums.size()) {
    create_line_tree(nums, root, 0, n-1);
}

void NumArray_v3::update(int idx, int val) {
    update_line_tree(root, idx, val);
    (*nums)[idx] = val;
}

int NumArray_v3::sumRange(int i, int j) {
    int sum = sum_range_line_tree(root, i, j);
    return sum;
}

} // namespace line_tree_alg

