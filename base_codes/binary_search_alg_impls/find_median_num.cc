#include<vector>
#include <algorithm>

#include "../binary_search.h"

int binary_search::dfs_find_median_num(std::vector<int>& nums1, int low1, std::vector<int>& nums2, int low2, int k) {
    if (k==1) {
        if (low1==nums1.size()) return nums2[low2];
        if (low2==nums2.size()) return nums1[low1];
        return std::min(nums1[low1], nums2[low2]);
    }
    
    int mid_1 = INT32_MAX;
    int mid_2 = INT32_MAX;
    if (low1 + k/2 -1 < nums1.size()) mid_1 = nums1[low1 + k/2 -1];
    if (low2 + k/2 -1 < nums2.size()) mid_2 = nums2[low2 + k/2 -1];
    if (mid_1 < mid_2) {
        return dfs_find_median_num(nums1, low1 + k/2, nums2, low2, k - k/2);
    }
    else {
        return dfs_find_median_num(nums1, low1, nums2, low2+k/2, k - k/2);
    }
}

double binary_search::findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    if (m==1 && n==1) return (nums1[0]+nums2[0])/2.0;
    int mid1 = (m+n+1)/2;
    int mid2 = (m+n+2)/2;
    int val1 = dfs_find_median_num(nums1, 0, nums2, 0, mid1);
    int val2 = dfs_find_median_num(nums1, 0, nums2, 0, mid2);
    return (val1 + val2) / 2.0;
}