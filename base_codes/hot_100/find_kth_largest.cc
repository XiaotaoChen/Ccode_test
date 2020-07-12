#include <vector>
#include "../hot_100.h"

namespace hot_100
{

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int parition(std::vector<int>& nums, int left, int right) {
    if (left >=right) return left;
    int val = nums[left];
    while(left < right) {
        while(right>left && nums[right]>=val) right--;
        nums[left] = nums[right];
        while(left < right && nums[left]<=val) left++;
        nums[right] = nums[left];
    }
    nums[left] = val;
    return left;
}

void partition_dfs(std::vector<int>& nums, int left, int right, int target_idx) {
    int mid = parition(nums, left, right);
    if (mid == target_idx) return;
    if (mid < target_idx) partition_dfs(nums, mid+1, right, target_idx);
    else partition_dfs(nums, left, mid-1, target_idx);
}

int findKthLargest(std::vector<int>& nums, int k) {
    if (nums.size() < k) return -1;
    int target_idx = nums.size() - k;
    partition_dfs(nums, 0, nums.size()-1, target_idx);
    return nums[target_idx];
}


void heap_modify(std::vector<int>& nums, int left, int right) {
    int dad = left;
    int son = 2 * dad + 1;
    while(son <= right) {
        if (son+1 <= right && nums[son] > nums[son+1]) son++;
        if (nums[dad] < nums[son]) return;
        swap(nums[dad], nums[son]);
        dad = son;
        son = 2 * dad +1;
    }
}

int findKthLargest_min_heap(std::vector<int>& nums, int k) {

    // make heap
    for (int i=k/2-1; i>=0; i--) {
        heap_modify(nums, i, k-1);
    }
    for (int i=k; i<nums.size(); i++) {
        if (nums[i] > nums[0]) {
            swap(nums[i], nums[0]);
            heap_modify(nums, 0, k-1);
        }
    }
    return nums[0];
}


} // namespace hot_100
