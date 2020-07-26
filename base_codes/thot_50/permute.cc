#include <vector>
#include "../thot_50.h"

namespace thot_50
{

void permute_dfs(std::vector<std::vector<int>>& combinations, std::vector<int>& curr,  std::vector<int>& nums, std::vector<bool>& visited) {
    if (curr.size() == nums.size()) {
        combinations.push_back(curr);
        return ;
    }
    for (int i=0; i<nums.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        curr.push_back(nums[i]);
        permute_dfs(combinations, curr, nums, visited);
        curr.pop_back();
        visited[i] = false;
    }
    return;
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> curr;
    std::vector<bool> visited(nums.size(), false);
    permute_dfs(result, curr, nums, visited);
    return result;
}

} // namespace thot_50
