#include <vector>
#include <algorithm>
#include "../minimization_algs.h"

namespace minimization_alg
{

int getMoneyAmount(int n) {
    if (n<2) return 0;
    if (n==2) return 1;
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, INT32_MAX));
    // dp[i][i]=0;
    for (int i=1; i<=n; i++) dp[i][i] = 0;
    
    for (int i=n-1; i>0; i--) {
        for (int j=i+1; j<=n; j++) {
            dp[i][j] = i + dp[i+1][j];
            for (int k=i+1; k<j; k++){
                dp[i][j] = std::min(dp[i][j], k + std::max(dp[i][k-1], dp[k+1][j]));
            }
            dp[i][j] = std::min(dp[i][j], j + dp[i][j-1]);
        }
    }
    return dp[1][n];
}

} // namespace minimization_alg
