#include <vector>

#include "../sorts.h"

namespace sort
{

int partition(std::vector<int>& vec, int low, int high) {
    int val = vec[low];
    while(low < high) {
        while(low < high && val <= vec[high]) high--;
        if (low < high) vec[low] = vec[high];
        while(low < high && val >= vec[low]) low++;
        if (low < high) vec[high] = vec[low];
    }
    vec[low] = val;
    return low;
}

void qsort_3_rec(std::vector<int>& vec, int low, int high) {
    if (low ==  high) return;
    int index = partition(vec, low, high);
    if (index >low) qsort_3_rec(vec, low, index-1);
    if (index < high) qsort_3_rec(vec, index+1, high);
}

void qsort_v3(std::vector<int>& vec) {
    if (vec.size()==0) return;
    qsort_3_rec(vec, 0, vec.size()-1);
}

} // namespace sort
