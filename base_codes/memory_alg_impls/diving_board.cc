#include<vector>

#include "../memory_algs.h"

std::vector<int> memory_alg::divingBoard(int shorter, int longer, int k) {
    if (k==0) return std::vector<int>();
    if (shorter == longer) return std::vector<int>(1, k*shorter);

    std::vector<int> result;
    for (int i=k; i>=0; i--) {
        result.push_back(i* shorter + (k-i) * longer);        
    } 
    return result;
}