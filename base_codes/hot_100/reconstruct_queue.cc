#include <vector>
#include <list>
#include <algorithm>
#include "../hot_100.h"

namespace hot_100
{

bool compare(const std::vector<int>& a, const std::vector<int>& b) {
    return a[0] == b[0] ? a[1] <= b[1]: a[0] > b[0];
}

std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
    if (people.size()<2) return people;
    std::sort(people.begin(), people.end(), compare);

    std::list<std::vector<int>> inter_result;
    for (int i=0; i<people.size(); i++) {
        auto pos = inter_result.begin();
        std::advance(pos, people[i][1]);
        inter_result.insert(pos, people[i]);
    }

    return std::vector<std::vector<int>>(inter_result.begin(), inter_result.end());
}

} // namespace hot_100
