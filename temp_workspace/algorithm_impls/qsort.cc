#include <vector>
#include "../algorithms.h"

namespace algorithms
{

void qsort(std::vector<int>& arr, int begin, int end) {
    int idx = partition(arr, begin, end);
    if (idx -1 >begin) qsort(arr, begin, idx-1);
    if (idx+1 < end) qsort(arr, idx+1, end);
}


int partition(std::vector<int>& arr, int begin, int end) {
    if (begin==end) return begin;
    int ref = arr[begin];
    while(begin < end) {
        while(begin < end && ref <=arr[end]) end--;
        if (begin < end) {
            arr[begin] = arr[end];
            begin++;
        }
        
        while(begin < end && ref >= arr[begin]) begin++;
        if (begin < end) {
            arr[end] = arr[begin];
            end--;
        }
    }
    arr[begin] = ref;
    return begin;
}


} // namespace algorithms
