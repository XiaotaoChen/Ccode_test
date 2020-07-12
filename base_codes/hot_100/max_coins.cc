#include <vector>
#include "../hot_100.h"

namespace hot_100
{

int maxCoins(std::vector<int>& nums) {
    int n = nums.size();
    if (n==0) return 0;
    if (n==1) return nums[0];
    
    int points[n+2];
    for (int i=0; i<n; i++) points[i+1] = nums[i];
    points[0] = points[n+1] = 1;
    
    int dp[n+2][n+2];
    std::fill_n(dp[0], (n+2)*(n+2), 0);

    for (int i=n; i>=0; i--) {
        for (int j=i+1; j<n+2; j++) {
            for (int k=i+1; k<j; k++) {
                dp[i][j] = std::max(
                    dp[i][j], 
                    dp[i][k] + dp[k][j] + points[i] * points[k]*points[j]);
            }
        }
    }
    return dp[0][n+1];
}

} // namespace hot_100
