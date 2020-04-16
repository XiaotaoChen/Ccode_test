#ifndef SORT_ALG_
#define SORT_ALG_


#include<cstdio>
#include <vector>

namespace sort
{

void qsort(int *arr, int low, int high);

void heap_sort(int *arr, int low, int high);

void heap_modify(int *arr, int low, int high);

void swap(int* a, int* b);

int maximumGap(std::vector<int>& nums);

int maximumGap_v2(std::vector<int>& nums);

void merge_two_arr(std::vector<int>& nums, int begin, int mid, int end);

// https://leetcode-cn.com/problems/reverse-pairs/
int merge_sort_reverse_pair(std::vector<int>& nums, int begin, int end);

int partition_qsort(int *arr, int low, int high);
void qsort_v2(int *arr, int low, int high);


} // namespace sort

#endif // SORT_ALG_