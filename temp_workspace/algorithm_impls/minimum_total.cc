#include <vector>
#include <climits>
#include <algorithm>

namespace algorithms
{

int minimumTotal(std::vector<std::vector<int> >& triangle) {
    if (triangle.size()==0) return 0;
    int n = triangle.size();
    int dp[2][n];
    std::fill_n(dp[0], n*2, INT_MAX);
    dp[0][0]=triangle[0][0];
    for (int i=1; i<n; i++) {
        int curr_idx = i%2;
        int last_idx = (i-1)%2;
        dp[curr_idx][0] = dp[last_idx][0] + triangle[i][0];
        for (int j=1; j<=i; j++) {
            dp[curr_idx][j] = std::min(dp[last_idx][j], dp[last_idx][j-1]) + triangle[i][j];
        }
    }
    int curr_idx = (n-1)%2;
    int result = *std::min_element(dp[curr_idx], dp[curr_idx]+n);
    return result;
}

} // namespace algorithms
