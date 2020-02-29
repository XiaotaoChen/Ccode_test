#include <vector>
#include <algorithm>

#include "../trace_back_algs.h"

void track_back::track_back_combination_sum(std::vector<std::vector<int>>& combinations, std::vector<int> curr, std::vector<int>& candidates, int index, int target) {
    if (target == 0) {
        combinations.push_back(curr);
        return;
    }

    for (int i=index; i<candidates.size(); i++) {
        if (i>index && candidates[i] == candidates[i-1]) continue;
        if (candidates[i] <= target) {
            curr.push_back(candidates[i]);
            track_back_combination_sum(combinations, curr, candidates, i+1, target-candidates[i]);
            curr.erase(--curr.end());
        }
        else {
            return;
        }
    }
}

std::vector<std::vector<int>> track_back::combinationSum2(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::sort(candidates.begin(), candidates.end());
    track_back_combination_sum(result, std::vector<int>(), candidates, 0, target);
    return result;
}