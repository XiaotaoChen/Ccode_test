#ifndef BINARY_SEARCH_ALGS_
#define BINARY_SEARCH_ALGS_

#include <vector>

namespace binary_search {

// https://leetcode-cn.com/problems/divide-two-integers/

int divide(int dividend, int divisor);

// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
int search(std::vector<int>& nums, int target);
int dfs_search(std::vector<int>& nums, int start, int end , int target);

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);
int dfs_find_median_num(std::vector<int>& nums1, int low1, std::vector<int>& nums2, int low2, int k);


}

#endif