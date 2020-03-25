#include <vector>
#include <algorithm>
#include "../geometric_algs.h"

namespace geometric_alg
{

int minTimeToVisitAllPoints(std::vector<std::vector<int>>& points) {
    if (points.size()==1) return 0;
    int n = points.size();
    int result = 0;
    for (int i=1; i<n; i++) {
        std::pair<int,int> p = {points[i][0] - points[i-1][0], points[i][1] - points[i-1][1]};
        result += std::max(std::abs(p.first), std::abs(p.second));
    }
    return result;
}

} // namespace geometric_alg
