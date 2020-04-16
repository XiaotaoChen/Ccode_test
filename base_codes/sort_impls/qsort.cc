#include<cstdio>

#include "../sorts.h"

namespace sort
{

void qsort(int *arr, int low, int high) {
    if (low==high) return;
    int ref = arr[low];
    int i = low;
    int j = high;
    while(i < j) {
        while(arr[j] >= ref  && j>i) j--;
        if (j>i) arr[i] = arr[j];
        while(arr[i] < ref && i < j) i++;
        if (i < j) arr[j] = arr[i];
    }
    arr[j] = ref;
    if (low < j-1) {
        qsort(arr, low, j -1);
    }
    if (j+1 < high) {
        qsort(arr, j+1, high);
    }
}

int partition_qsort(int *arr, int low, int high) {
    int small = low -1;
    for (int i=low; i<high; i++) {
        if (arr[i] < arr[high]) {
            small++;
            if(small != i) swap(arr+small, arr+i);
        }
    }
    small++;
    swap(arr+small, arr+high);
    return small;
}

void qsort_v2(int *arr, int low, int high) {
    if (low == high) return ;
    int mid = partition_qsort(arr, low, high);
    if (mid>low) qsort_v2(arr, low, mid-1);
    if (mid<high) qsort_v2(arr, mid+1, high);
}


} // namespace sort
