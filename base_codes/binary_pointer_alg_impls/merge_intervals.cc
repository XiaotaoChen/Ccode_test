#include <vector>
#include <algorithm>

#include "../binary_pointer.h"

namespace binary_pointer
{

std::vector<std::vector<int>> merge_intervals(std::vector<std::vector<int>>& intervals) {
    std::vector<std::vector<int>> result;

    std::sort(intervals.begin(), intervals.end());
    int left = intervals[0][0];
    int right = intervals[0][1];
    for (int i=1; i < intervals.size(); i++) {
        if (right >=intervals[i][0]) {
            right = right > intervals[i][1] ? right : intervals[i][1];
        }
        else {
            result.push_back({left, right});
            left = intervals[i][0];
            right = intervals[i][1];
        }
    }
    result.push_back({left, right});

    return result;
}

} // namespace binary_pointer
