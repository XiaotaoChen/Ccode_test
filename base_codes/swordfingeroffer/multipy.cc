#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::vector<int> multipy(std::vector<int>& arr) {
    std::vector<int> result;
    int len = arr.size();
    if (len == 0) return result;
    if (len==1) {
        result.push_back(1);
        return result;
    }

    int heads[len];
    int tails[len];
    heads[0] = arr[0];
    for (int i=1; i< len-1; i++) heads[i] = heads[i-1] * arr[i];

    tails[len-1] = arr[len-1];
    for (int i=len-2; i>0; i--) tails[i] = tails[i+1] * arr[i];


    result.push_back(tails[1]);
    for (int i=1; i<len-1; i++) {
        result.push_back(heads[i-1] * tails[i+1]);
    }
    result.push_back(heads[len-2]);
    return result;
}

} // namespace sword_finger_offer
