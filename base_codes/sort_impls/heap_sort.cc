
#include "../sorts.h"

void sort::swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void sort::heap_modify(int *arr, int start, int end) {
    int dad = start;
    int son = 2 * dad +1;
    while(son <= end) {
        if (son + 1 <=end && arr[son] < arr[son+1]) son++;
        if (arr[dad] >= arr[son]) return;
        
        swap(&arr[dad], &arr[son]);
        dad = son;
        son = 2 * dad +1;
    }
}

void sort::heap_sort(int *arr, int start, int end) {
    // get max element
    int length = end - start +1;
    for (int i=length/2-1; i>=0; i--) {
        heap_modify(arr, i, end);
    }
    for (int i=length-1; i>0; i--) {
        swap(&arr[0], &arr[i]);
        heap_modify(arr, 0, i-1);
    }
    return;
}