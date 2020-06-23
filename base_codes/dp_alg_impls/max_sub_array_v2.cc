#include <vector>
#include "../dp_algs.h"

namespace dp
{

int maxSubArray_v2(std::vector<int>& nums) {
    if (nums.size()==0) return 0;
    int curr = nums[0];
    int result = curr;
    for (int i=1; i<nums.size(); i++) {
        if (curr <0) {
            curr = nums[i];
        }
        else {
            curr += nums[i];
        }
        result = result > curr ? result : curr;
    }
    return result;
}

} // namespace dp
