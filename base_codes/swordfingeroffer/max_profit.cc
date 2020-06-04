#include <vector>
#include <climits>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int maxprofit(std::vector<int>& arr) {
    if (arr.size() < 2) return 0;
    int result = INT32_MIN;
    int curr_min = arr[0];
    for (int i=1; i < arr.size(); i++) {
        int tmp = arr[i] - curr_min;
        result = result > tmp ? result : tmp;
        curr_min = curr_min < arr[i] ? curr_min : arr[i];
    }
    return result;
}

} // namespace sword_finger_offer
