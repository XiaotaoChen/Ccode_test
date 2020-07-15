#include <vector>
#include <climits>
#include <algorithm>
#include "../algorithms.h"

namespace algorithms
{

int maxProduct(std::vector<int>& nums) {
    int n = nums.size();
    if (n==0) return -1;
    if (n==1) return nums[0];

    // dp[0] max, dp[1] for min
    int dp[2][n];

    std::fill_n(dp[0], n, INT_MIN);
    std::fill_n(dp[1], n, INT_MAX);
    dp[0][0] = dp[1][0] = nums[0];
    int result = dp[0][0];
    for (int i=1; i<n; i++) {
        dp[0][i] = std::max(nums[i], std::max(dp[0][i-1] * nums[i], dp[1][i-1] * nums[i]));
        dp[1][i] = std::min(nums[i], std::min(dp[0][i-1] * nums[i], dp[1][i-1] * nums[i]));
        result = std::max(dp[0][i], result);
    }
    return result;
}

} // namespace algorithms
