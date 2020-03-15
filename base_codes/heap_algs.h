#ifndef HEAD_ALGS_
#define HEAD_ALGS_

#include <vector>

#include "data_structs/base_struct.h"

namespace heap {

// https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
int findKthLargest(std::vector<int>& nums, int k);
int qsort_pilvot(std::vector<int>&nums, int low, int high);

void swap(int *a, int *b);
void swap(int &a, int &b);
void min_k_heap(std::vector<int>& nums, int start, int end);
int findKthLargest_v2(std::vector<int>& nums, int k);

// https://leetcode-cn.com/problems/merge-k-sorted-lists/
ListNode* mergeKLists(std::vector<ListNode*>& lists);
ListNode* meregeTwoList(ListNode* root1, ListNode* root2);
ListNode* mergeKLists(std::vector<ListNode*>& lists, int start, int end);

}

#endif