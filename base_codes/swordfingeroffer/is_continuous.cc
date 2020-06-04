#include <vector>
#include <algorithm>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool compare_inc(int a, int b) {
    return a < b;
}

bool isContinuous(std::vector<int>& arr) {
    if ( arr.size()<5 ) return false;
    std::sort(arr.begin(), arr.end(), compare_inc);
    
    int numofzero = 0;
    int idx=0;
    while(arr[idx]==0) {
        numofzero++;
        idx++;
    }

    int gap_distance = 0;
    // skip first nonzero number
    idx++;
    while(idx<arr.size()) {
        if (arr[idx] == arr[idx-1]) return false;
        gap_distance+= (arr[idx] - arr[idx-1]-1);
        idx++;
    }

    if (gap_distance <= numofzero) return true;
    return false;
}

} // namespace sword_finger_offer
