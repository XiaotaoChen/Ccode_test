#include <vector>
#include <algorithm>
#include "../bfs_algs.h"

namespace bfs
{

void dfs_combinationsum(std::vector<std::vector<int>> & combinations, std::vector<int>& curr, std::vector<int>& candidates, int idx, int target) {
    if (target == 0) {
        combinations.push_back(curr);
        return;
    }
    if (target < 0 || idx >= candidates.size()) return;

    for (int i=idx; i<candidates.size(); i++) {
        if (target - candidates[i]<0) continue;
        curr.push_back(candidates[i]);
        dfs_combinationsum(combinations, curr, candidates, i, target- candidates[i]);
        curr.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    if (candidates.size()==0) return result;
    std::sort(candidates.begin(), candidates.end());// 可以去掉

    std::vector<int> curr;

    dfs_combinationsum(result, curr, candidates, 0, target);

    return result;
}


} // namespace bfs
