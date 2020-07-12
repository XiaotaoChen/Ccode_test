#include <vector>
#include "../hot_100.h"

namespace hot_100
{

std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
    int n = nums.size();
    for (int i=0; i<n; i++) {
        int idx = (nums[i]-1)%n;
        nums[idx]+=n;
    }
    std::vector<int> result;
    for (int i=0; i<n; i++) {
        if (nums[i]<=n) {
            result.push_back(i+1);
        }
    }
    return result;
}

} // namespace hot_100
