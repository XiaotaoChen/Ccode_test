#ifndef GEOMETRIC_ALG_
#define GEOMETRIC_ALG_

#include <vector>

namespace geometric_alg
{

// https://leetcode-cn.com/problems/surface-area-of-3d-shapes
int surfaceArea(std::vector<std::vector<int>>& grid);

// https://leetcode-cn.com/problems/check-if-it-is-a-straight-line/
bool checkStraightLine(std::vector<std::vector<int>>& coordinates);

int gcd(int x, int y);

// https://leetcode-cn.com/problems/minimum-time-visiting-all-points/
int minTimeToVisitAllPoints(std::vector<std::vector<int>>& points);

// https://leetcode-cn.com/problems/intersection-lcci/
std::vector<double> intersection(std::vector<int>& start1, std::vector<int>& end1, std::vector<int>& start2, std::vector<int>& end2);


} // namespace geometric_alg


#endif