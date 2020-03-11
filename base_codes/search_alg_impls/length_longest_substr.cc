#include<cstdio>
#include<string>

#include "../search_algs.h"

double search::findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int left1 = 0;
    int left2 = 0;
    int size1 = nums1.size();
    int size2 = nums2.size();
    std::vector<int> arr;
    while(left1 < size1 && left2 < size2) {
        if (nums1[left1] < nums2[left2]) {
            arr.push_back(nums1[left1]);
            left1 ++;
        }
        else {
            arr.push_back(nums2[left2]);
            left2 ++;
        }
    }
    while(left1 < size1) {
        arr.push_back(nums1[left1]);
        left1 ++;
    }
    while(left2 < size2) {
        arr.push_back(nums2[left2]);
        left2 ++;
    }

    int len = arr.size();
    if (len==1) return arr[0];
    double mid_idx = (len + 1)/2 -1;
    if (len % 2 == 1) return arr[mid_idx];
    return (arr[mid_idx] + arr[mid_idx + 1]) / 2.0;
}

int search::mid_val_k(std::vector<int>& nums1, int low1, std::vector<int>& nums2, int low2, int k) {
    if (k == 1) {
        if (low1 == nums1.size()) return nums2[low2];
        if (low2 == nums2.size()) return nums1[low1];
        return std::min(nums1[low1], nums2[low2]);
    }
    int mid1 = INT32_MAX;
    int mid2 = INT32_MAX;
    if ((low1 + k/2-1) < nums1.size()) mid1 = nums1[low1 + k/2-1];
    if ((low2 + k/2-1) < nums2.size()) mid2 = nums2[low2 + k/2-1];
    if (mid1 < mid2) {
        return mid_val_k(nums1, low1 + k/2, nums2, low2, k - k/2);
    }
    else {
        return mid_val_k(nums1, low1, nums2, low2 + k/2, k - k/2);
    }
}

double search::findMedianSortedArrays_v2(std::vector<int>& nums1, std::vector<int>& nums2) {
    int len = nums1.size() + nums2.size();
    int k1 = (len +1) / 2;
    int k2 = (len +2) / 2;
    int mid1 = mid_val_k(nums1, 0, nums2, 0, k1);
    int mid2 = mid_val_k(nums1, 0, nums2, 0, k2);
    return (mid1 + mid2) / 2.0;
}