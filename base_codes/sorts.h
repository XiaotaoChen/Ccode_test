#ifndef SORT_ALG_
#define SORT_ALG_


#include<cstdio>

namespace sort
{

void qsort(int *arr, int low, int high);

void heap_sort(int *arr, int low, int high);

void heap_modify(int *arr, int low, int high);

void swap(int* a, int* b);

} // namespace sort

#endif // SORT_ALG_