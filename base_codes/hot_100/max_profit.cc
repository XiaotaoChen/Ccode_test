#include <vector>
#include <algorithm>
#include "../hot_100.h"

namespace hot_100
{

int maxProfit(std::vector<int>& prices) {
    int n = prices.size();
    if (n <2) return 0;
    int dp[n+1][3];
    std::fill_n(dp[0], (n+1)*3, INT32_MIN);
    dp[0][0]=0;
    for (int i=0; i<n; i++) {
        dp[i+1][0] = std::max(dp[i][0], dp[i][2]);
        dp[i+1][1] = std::max(dp[i][1], dp[i][0]-prices[i]);
        dp[i+1][2] = dp[i][1] + prices[i];
    }
    return std::max(dp[n][0], dp[n][2]);
}

} // namespace hot_100
