#include <vector>
#include "../bits_algs.h"

namespace bits_alg
{

int singleNumber(std::vector<int>& nums) {
    if (nums.size() ==0) return 0;
    if (nums.size() == 1) return nums[0];
    int result = 0;
    for (int i=0; i<nums.size(); i++) {
        result ^= nums[i];
    }
    return result;
}

} // namespace bits_alg
