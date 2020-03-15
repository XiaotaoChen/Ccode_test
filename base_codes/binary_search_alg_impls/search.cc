#include<vector>

#include "../binary_search.h"

int binary_search::dfs_search(std::vector<int>& nums, int start, int end , int target) {
    if (start == end){
        if (nums[start] == target) return start;
        return -1;
    }
    if (start >end) return -1;
    
    int mid = (start + end) / 2;
    if (target == nums[mid]) return mid;
    int idx = -1;
    if (nums[start] <= nums[mid]) {
        if (target >=nums[start] && target <=nums[mid]) {
            idx = dfs_search(nums, start, mid-1, target);
        }
        else {
            idx = dfs_search(nums, mid+1, end, target);
        }
    }
    else {
        if (target >= nums[mid] && target <= nums[end]) {
            idx = dfs_search(nums, mid+1, end, target);
        }
        else {
            idx = dfs_search(nums, start, mid-1, target);
        }
        // if (nums[start] <= target || nums[mid] >= target) {
            //      前半部分是乱序的， 当4 5 6 1,2, 如当nums[2]时，只有当 nums[start]<=target || nums[mid]>= target
        //     idx = dfs_search(nums, start, mid-1, target);
        // }
        // else {
        //     idx = dfs_search(nums, mid+1, end, target);
        // }
    }
    return idx;
}

int binary_search::search(std::vector<int>& nums, int target) {
    return dfs_search(nums, 0, nums.size()-1, target);
}