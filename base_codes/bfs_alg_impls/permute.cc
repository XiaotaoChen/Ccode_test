#include <vector>
#include "../bfs_algs.h"

namespace bfs
{

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void dfs_permute(std::vector<std::vector<int>>& combinations, int depth, std::vector<int>& nums) {
    if (depth == nums.size()) {
        combinations.push_back(nums);
        return;
    }

    for (int i=depth; i<nums.size(); i++) {
        swap(nums[depth], nums[i]);
        dfs_permute(combinations, depth+1, nums);
        swap(nums[depth], nums[i]);
    }
    return;
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    dfs_permute(result, 0, nums);
    return result;
}


} // namespace bfs
