#include<cstdio>
#include<string>

#include "../search_algs.h"

int search::is_include(std::string s, int left, int right, char ch) {
    for (int i=left; i<=right; i++) {
        if (s[i] == ch) return i;
    }
    return -1;
}

int search::lengthOfLongestSubstring(std::string s) {
    if (s.length() <= 1) return s.length();
    int result = 1;
    int curr_left = 0;
    for (int i=1; i< s.length(); i++) {
        int idx = is_include(s, curr_left, i -1, s[i]);
        if ( idx >= 0) {
            // is included
            curr_left = idx +1;
        }
        result = std::max(i - curr_left +1, result);
    }
    return result;
}

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