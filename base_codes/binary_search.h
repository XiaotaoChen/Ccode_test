#ifndef BINARY_SEARCH_ALGS_
#define BINARY_SEARCH_ALGS_

#include <vector>
#include "data_structs/base_struct.h"

namespace binary_search {

// https://leetcode-cn.com/problems/divide-two-integers/

int divide(int dividend, int divisor);

// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
int search(std::vector<int>& nums, int target);
int dfs_search(std::vector<int>& nums, int start, int end , int target);

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);
int dfs_find_median_num(std::vector<int>& nums1, int low1, std::vector<int>& nums2, int low2, int k);

// https://leetcode-cn.com/problems/binode-lcci/
TreeNode* convertBiNode(TreeNode* root);
void dfs_binode(TreeNode* root, TreeNode*& pre);

// https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/
TreeNode* bstToGst(TreeNode* root);

void dfs_bstToGst(TreeNode* root, TreeNode*& pre);

// https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/
int dfs_max_path_sum(TreeNode* root, int& curr);
int maxPathSum(TreeNode* root);

// https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
std::vector<int> searchRange(std::vector<int>& nums, int target);
int dfs_searchrange(std::vector<int>& nums, int target, int left, int right);


std::vector<int> searchRange_v2(std::vector<int>& nums, int target);

// https://leetcode-cn.com/problems/search-a-2d-matrix/
bool dfs_searchmatrix(std::vector<std::vector<int>>& matrix, int start, int end, int target);

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target);

// https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/
int kthSmallest(std::vector<std::vector<int>>& matrix, int k);
int kthsmallest_cnt(std::vector<std::vector<int>> & matrix, int val);


// search next node
TreeLinkNode* next_node(TreeLinkNode* node);

// https://leetcode-cn.com/problems/search-insert-position/
int searchInsert(std::vector<int>& nums, int target);

int searchInsert_v2(std::vector<int>& nums, int target);

}

#endif