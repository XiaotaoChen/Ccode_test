#include <vector>
#include "../binary_search.h"

namespace binary_search
{

int searchInsert_dfs(std::vector<int>& nums, int target, int left, int right) {
    if (left == right) return right;
    int mid = (left + right) / 2;
    if (nums[mid]==target) return mid;
    if (nums[mid] < target) return searchInsert_dfs(nums, target, mid+1, right);
    return searchInsert_dfs(nums, target, left, mid);
}

int searchInsert(std::vector<int>& nums, int target) {
    int idx = searchInsert_dfs(nums, target, 0, nums.size() -1);
    if (nums[idx]==target) return idx;
    if (idx == nums.size()-1 && nums[idx] < target) {
        nums.insert(nums.end(), target);
        return idx+1;
    }
    nums.insert(nums.begin() + idx, target);
    return idx;
}

int searchInsert_v2(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] < target) {
            left = mid+1;
        }
        // 这种写法保证了区间右侧的数一定是大于或等于target, 除非target比最大值大．
        else {
            right = mid;
        }
    }
    if (nums[left] == target) return left;
    if (left==nums.size()-1 && nums[left] < target) {
        nums.insert(nums.end(), target);
        return left+1;
    }
    else {
        nums.insert(nums.begin()+left, target);
        return left;
    }
}

} // namespace binary_search
