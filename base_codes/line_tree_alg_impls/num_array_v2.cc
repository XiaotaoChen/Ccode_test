#include <vector>
#include "../line_tree_algs.h"
namespace line_tree_alg
{


NumArray_v2::NumArray_v2(std::vector<int>& nums): nums(&nums), sums(nums.size()+1), n(nums.size()) {
    std::vector<int> pre_sum(sums);
    for (int i=1; i<=n;i++) {
        pre_sum[i] = pre_sum[i-1] + nums[i-1];
    }
    for (int i=1; i<=n; i++) {
        sums[i] = pre_sum[i] - pre_sum[i - lowbit(i)];
    }
}

int NumArray_v2::lowbit(int x) {
    return x & (-x);
}

void NumArray_v2::update(int i, int val) {
    int d = val - (*nums)[i];
    for (int x=i+1; x<=n; x+=lowbit(x)) {
        sums[x] += d;
    }
    (*nums)[i] = val;
}

int NumArray_v2::sumRange(int i, int j) {
    int sum_j = 0;
    for (int x=j+1; x>0; x-=lowbit(x)) {
        sum_j += sums[x];
    }
    int sum_i = 0; // sum(0->i-1)
    for (int x=i; x>0; x-=lowbit(x)) sum_i += sums[x];
    return sum_j - sum_i;
}

} // namespace line_tree_alg
