#include <vector>
#include <set>
#include <algorithm>

#include "../line_tree_algs.h"

namespace line_tree_alg
{

std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
    std::vector<std::vector<int>> result;
    std::vector<std::pair<int ,int>> all;
    for (int i=0; i<buildings.size(); i++ ){
        all.push_back({buildings[i][0], -buildings[i][2]});
        all.push_back({buildings[i][1], buildings[i][2]});
    }
    std::sort(all.begin(), all.end());

    int pre = 0; int curr = 0;
    // max heap
    std::multiset<int> curr_heights;
    for (std::pair<int ,int> p: all) {
        if (p.second <0) curr_heights.insert(-p.second);
        else curr_heights.erase(curr_heights.find(p.second));
        if (curr_heights.empty()) curr = 0;
        else curr = *curr_heights.rbegin();
        if (curr != pre) {
            result.push_back({p.first, curr});
            pre = curr;
        }
    }
    return result;
}



} // namespace line_tree_alg
