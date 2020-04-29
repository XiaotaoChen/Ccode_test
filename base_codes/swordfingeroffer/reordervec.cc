#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void reorderVec(std::vector<int>& vec, bool(*func)(int)) {
    if (vec.size() < 2) return ;
    int start = 0;
    int end = vec.size() - 1;
    
    int small = start-1;
    for (; start < end; start++) {
        // if (vec[start] < vec[end]) {
            if (func(vec[start])) {
            small++;
            if (small != start) swap(vec[small], vec[start]);
        }
    }
    small++;
    swap(vec[small], vec[end]);
}

} // namespace sword_finger_offer
