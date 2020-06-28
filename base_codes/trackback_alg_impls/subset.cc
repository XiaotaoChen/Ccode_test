#include <vector>
#include "../trace_back_algs.h"

namespace track_back
{

void subset_track_back(std::vector<std::vector<int>>& combinations, std::vector<int> curr, std::vector<int>& nums, int index) {
    combinations.push_back(curr);
    for (int i=index; i<nums.size(); i++) {
        curr.push_back(nums[i]);
        subset_track_back(combinations, curr, nums, i+1);
        curr.pop_back();
    }
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    subset_track_back(result, {}, nums, 0);
    return result;
}

} // namespace track_back
