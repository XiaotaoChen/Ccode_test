#include <vector>
#include <algorithm>
#include "../line_tree_algs.h"

namespace line_tree_alg
{

void update(std::vector<int>& BIT, int index, int val)
{
    while (index > 0) {
        BIT[index] += val;
        index -= index & (-index);
    }
}

int query(std::vector<int>& BIT, int index)
{
    int sum = 0;
    while (index < BIT.size()) {
        sum += BIT[index];
        index += index & (-index);
    }
    return sum;
}
int reversePairs(std::vector<int>& nums)
{
    int n = nums.size();
    std::vector<int> nums_copy(nums);

    sort(nums_copy.begin(), nums_copy.end());
    for (int i=0; i<nums_copy.size(); i++) printf("%d ", nums_copy[i]);
    printf("\n");

    std::vector<int> BITS(n + 1, 0);
    int count = 0;
    for (int i = 0; i < n; i++) {
        auto iter = lower_bound(nums_copy.begin(), nums_copy.end(), 2LL * nums[i] + 1);
        printf("%d\n", *iter);
        count += query(BITS, lower_bound(nums_copy.begin(), nums_copy.end(), 2LL * nums[i] + 1) - nums_copy.begin() + 1);
        iter = lower_bound(nums_copy.begin(), nums_copy.end(), nums[i]);
        printf("%d\n", *iter);
        update(BITS, lower_bound(nums_copy.begin(), nums_copy.end(), nums[i]) - nums_copy.begin() + 1, 1);
    }
    return count;
}


} // namespace line_tree_alg
