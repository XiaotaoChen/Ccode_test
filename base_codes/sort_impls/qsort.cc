#include<cstdio>

#include "../sorts.h"

void sort::qsort(int *arr, int low, int high) {
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