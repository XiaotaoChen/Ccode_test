#include <vector>
#include <algorithm>
#include "../bfs_algs.h"

namespace bfs
{

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void dfs_permute(std::vector<std::vector<int>>& combinations, int depth, std::vector<int>& nums) {
    if (depth == nums.size()) {
        combinations.push_back(nums);
        return;
    }

    for (int i=depth; i<nums.size(); i++) {
        swap(nums[depth], nums[i]);
        dfs_permute(combinations, depth+1, nums);
        swap(nums[depth], nums[i]);
    }
    return;
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    dfs_permute(result, 0, nums);
    return result;
}

void nextPermutation(std::vector<int>& nums) {
    if (nums.size()<=1) return;
    int idx = nums.size()-1;
    for (int i=nums.size()-1; i>0; i--) {
        if (nums[i]>nums[i-1]) {
            idx = i-1;
            break;
        }
    }
    if (idx==nums.size()-1) {
        std::reverse(nums.begin(), nums.end());
        return;
    }
    // find sub_min_idx
    // int sub_min_idx = -1;
    // int val = INT32_MAX;
    // for (int i=idx+1; i<nums.size(); i++) {
    //     if (nums[i]>nums[idx]) {
    //         val = nums[i] < val ? nums[i] : val;
    //         sub_min_idx = i;
    //     }
    // }
    // swap(nums[sub_min_idx], nums[idx]);
    // std::sort(nums.begin()+idx+1, nums.end());
    int sub_min_idx = nums.size() - 1;
    for (int i=nums.size() - 1; i>idx; i--) {
        if (nums[i]>nums[idx]) {
            sub_min_idx = i;
            break;
        }
    }
    swap(nums[sub_min_idx], nums[idx]);
    std::reverse(nums.begin()+idx+1, nums.end());
    return;
}


} // namespace bfs
