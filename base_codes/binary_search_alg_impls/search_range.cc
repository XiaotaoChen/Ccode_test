#include <vector>
#include "../binary_search.h"

namespace binary_search
{

int dfs_searchrange(std::vector<int>& nums, int target, int left, int right) {
    if (left>right) return -1;
    int mid = (left+right) /2;
    if (target==nums[mid]) return mid;
    if (target < nums[mid]) return dfs_searchrange(nums, target, left, mid-1);
    else return dfs_searchrange(nums, target, mid+1, right);
}

std::vector<int> searchRange(std::vector<int>& nums, int target) {
    if (nums.size()==0) return {-1,-1};
    int idx = dfs_searchrange(nums, target, 0, nums.size()-1);
    if (idx==-1) return {-1,-1};
    int left = idx;
    int right = idx;
    while(left-1>=0 && nums[left-1]==target) left--;
    while(right+1<nums.size() && nums[right+1]==target) right++;
    return {left, right};
}

} // namespace binary_search
