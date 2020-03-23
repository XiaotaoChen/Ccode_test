#include <vector>

#include "../sorts.h"

namespace sort
{

void merge_two_arr(std::vector<int>& nums, int begin, int mid, int end) {
    // std::vector<int> tmp(end-begin+1);
    int tmp[end-begin+1];
    int i=begin; int j=mid+1;
    int curr_idx=0;
    while(i<=mid && j<=end) {
        if (nums[i]<=nums[j]){
            tmp[curr_idx++] = nums[i++];
        }
        else{
            tmp[curr_idx++] = nums[j++];
        }
    }
    while(i<=mid) tmp[curr_idx++] = nums[i++];
    while(j<=end) tmp[curr_idx++] = nums[j++];
    for (i=begin, j=0; i<=end; i++,j++) {
        nums[i] = tmp[j];
    }
}

int merge_sort_reverse_pair(std::vector<int>& nums, int begin, int end) {
    if (begin==end) return 0;
    int mid = (begin+end)/2;
    int ans = 0;
    ans += merge_sort_reverse_pair(nums, begin, mid);
    ans += merge_sort_reverse_pair(nums, mid+1, end);
    int j = mid +1;
    for (int i=begin; i<=mid; i++) {
        while (j <= end && nums[i] > nums[j] * 2LL) j++;
        ans += j - (mid + 1);
    }
    merge_two_arr(nums, begin, mid, end);

    return ans;
}

} // namespace sort
