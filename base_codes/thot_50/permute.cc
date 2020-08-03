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

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void permute_v2_dfs(std::vector<std::vector<int>>& combinations, std::vector<int>& nums, int index) {
    if (index == nums.size()-1) {
        combinations.push_back(nums);
        return;
    }
    for (int i=index; i<nums.size(); i++) {
        swap(nums[index], nums[i]);
        permute_v2_dfs(combinations, nums, index+1);
        swap(nums[index], nums[i]);
    }
}

std::vector<std::vector<int>> permute_v2(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    permute_v2_dfs(result, nums, 0);
    return result;
}

} // namespace thot_50
