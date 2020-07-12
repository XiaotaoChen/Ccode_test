#include <vector>
#include <climits>
#include "../hot_100.h"

namespace hot_100
{

int numSquares(int n) {
    if (n==0) return 0;
    if (n==1) return 1;
    int dp[n+1];
    std::fill_n(dp, n+1, INT_MAX);
    dp[0] = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; i-j*j>=0; j++) {
            dp[i] = dp[i] < dp[i-j*j]+1 ? dp[i]: dp[i-j*j]+1;
        }
    }
    return dp[n];
}

} // namespace hot_100
