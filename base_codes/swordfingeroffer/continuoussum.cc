#include <vector>
#include <algorithm>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int continuoussum(std::vector<int>& arr) {
    if (arr.size()==0) return 0;
    int result = INT32_MIN;
    int curr = 0;
    for (int i=0; i<arr.size(); i++) {
        if (curr>0) {
            curr += arr[i];
        }
        else {
            curr = arr[i];
        }
        result = result > curr ? result : curr;
    }
    return result;
}

} // namespace sword_finger_offer
