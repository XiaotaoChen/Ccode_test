#include <vector>
#include "../bits_algs.h"

void bits_alg::trace_back_subset(std::vector<std::vector<int>>& combinations, std::vector<int> curr, std::vector<int>& nums, int idx) {
    if (idx == nums.size()) return;
    for (int i=idx; i<nums.size(); i++) {
        curr.push_back(nums[i]);
        combinations.push_back(curr);
        trace_back_subset(combinations, curr, nums, i+1);
        curr.pop_back();
    }
}

std::vector<std::vector<int>> bits_alg::subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    result.push_back(std::vector<int>());
    if (nums.size()==0) return result;
    std::vector<bool> visited(nums.size(), false);
    std::vector<int> curr;
    trace_back_subset(result, curr, nums, 0);
    return result;
}

std::vector<std::vector<int>> bits_alg::subsets_v2(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n==0) {
        result.push_back(std::vector<int>());
    }
    int total_n = 1<<n;
    for (int i=0; i<total_n; i++) {
        std::vector<int> curr;
        int tmp = i;
        for (int j=0; j<n;j++) {
            if (tmp & 1 == 1) curr.push_back(nums[j]);
            tmp = tmp>>1;
        }
        result.push_back(curr);
    }
    return result;
}