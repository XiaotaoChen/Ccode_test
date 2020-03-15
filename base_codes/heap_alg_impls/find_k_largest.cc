#include<vector>

#include "../heap_algs.h"

int heap::qsort_pilvot(std::vector<int>&nums, int low, int high) {
    int val = nums[low];
    while(low < high) {
        while (low < high && val >= nums[high]) high--;
        nums[low] = nums[high];
        
        while(low<high && val <= nums[low]) low++;
        nums[high] = nums[low];
    }
    nums[low] = val;
    return low;
}

int heap::findKthLargest(std::vector<int>& nums, int k) {

    int l = 0;
    int r = nums.size() -1;
    while(l <= r) {
        int idx = qsort_pilvot(nums, l, r);

        if (idx == k-1) return nums[idx];
        if (idx < k-1) {
            l = idx + 1;
        }
        else {
            r = idx - 1;
        }
    }
    return -1;
}

void heap::swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void heap::swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

void heap::min_k_heap(std::vector<int>& nums, int start, int end) {
    int dad = start;
    int son = 2 * dad +1;
    while (son <=end) {
        if (son+1<=end && nums[son] > nums[son+1]) son++;
        if (nums[dad] <= nums[son]) return;
        // swap(&nums[dad], &nums[son]);
        swap(nums[dad], nums[son]);
        dad = son;
        son = 2 * dad + 1;
    }
    return;
}

int heap::findKthLargest_v2(std::vector<int>& nums, int k) {
    if (nums.size()==1 && k==1) return nums[0];
    for (int i=k/2-1; i>=0; i--)
        min_k_heap(nums, i, k-1);
    for (int i=k; i<nums.size(); i++) {
        if (nums[i] <= nums[0]) continue;
        // swap(&nums[i], &nums[0]);
        swap(nums[i], nums[0]);
        min_k_heap(nums, 0, k-1);
    }
    return nums[0];
}
