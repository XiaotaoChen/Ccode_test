#include <vector>

#include "../thot_50.h"

namespace thot_50
{

void subset_dfs(std::vector<std::vector<int>>& combinations, std::vector<int>& curr, std::vector<int>& nums, int index) {
     combinations.push_back(curr);
     for (int i=index; i<nums.size(); i++) {
         curr.push_back(nums[i]);
         subset_dfs(combinations, curr, nums, i+1);
         curr.pop_back();
     }
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
     std::vector<std::vector<int>> result;
     std::vector<int> curr;
     subset_dfs(result, curr, nums, 0);
     return result;
}

} // namespace thot_50
