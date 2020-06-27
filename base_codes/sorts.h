#ifndef SORT_ALG_
#define SORT_ALG_


#include<cstdio>
#include <vector>

namespace sort
{

void qsort(int *arr, int low, int high);

int partition_qsort(int *arr, int low, int high);
void qsort_v2(int *arr, int low, int high);

void qsort_v3(std::vector<int>& vec);

void heap_sort(int *arr, int low, int high);

void heap_modify(int *arr, int low, int high);

void swap(int* a, int* b);

int maximumGap(std::vector<int>& nums);

int maximumGap_v2(std::vector<int>& nums);

int maximumGap_repeated(std::vector<int>& nums);

int maximumGap_v2_repeated(std::vector<int>& nums);

void merge_two_arr(std::vector<int>& nums, int begin, int mid, int end);

// https://leetcode-cn.com/problems/reverse-pairs/
int merge_sort_reverse_pair(std::vector<int>& nums, int begin, int end);



std::vector<int> topKFrequent(std::vector<int>& nums, int k);

std::vector<int> topKFrequent_v2(std::vector<int>& nums, int k);

// https://leetcode-cn.com/problems/h-index/
int h_index(std::vector<int>& citations);
int h_index_v2(std::vector<int>& citations);

// https://leetcode-cn.com/problems/sort-colors/
void sortColors(std::vector<int>& nums);


} // namespace sort

#endif // SORT_ALG_