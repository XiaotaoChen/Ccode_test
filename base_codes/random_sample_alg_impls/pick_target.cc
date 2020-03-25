#include <vector>
#include <cstdlib>   // rand
#include "../random_sample_algs.h"

namespace random_sample_alg
{

int pick_idx(std::vector<int>& nums, int target) {
    int count = 0;
    int result = -1;
    for (int i=0; i<nums.size(); i++) {
        if (nums[i]==target) {
            count++;
            int random_val = std::rand()%count;
            if (random_val==(count-1)) {
                result = i;
            }
        }
    }
    return result;
}

} // namespace random_sample_alg
