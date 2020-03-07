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
/* 
    递归遍历求和，先遍历: right, root, left. 记录一个pre节点，每个节点val=pre->val + val;
*/

TreeNode* bstToGst(TreeNode* root);

void dfs_bstToGst(TreeNode* root, TreeNode*& pre);

}

#endif