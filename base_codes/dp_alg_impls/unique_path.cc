#include "../dp_algs.h"

int dp::uniquePaths(int m, int n){
    if (m == 0 || n == 0) return 0;
    if (m ==1 || n == 1) return 1;
    int dp[m][n];
    dp[0][0] =1;
    for (int i=0; i<m; i++) dp[i][0] =1;
    for (int i=0; i<n; i++) dp[0][i] =1;
    
    for (int i=1; i<m; i++) {
        for (int j=1; j< n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[m-1][n-1];
}

int dp::uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    if (obstacleGrid.size()==0) return 0;
    if (obstacleGrid[0].size() ==0) return 0;
    if (obstacleGrid[0][0] == 1) return 0;
    
    int n = obstacleGrid.size();
    int m = obstacleGrid[0].size();
    long dp[n][m];
    std::fill_n(dp[0], n*m, 0);
    for (int i=0; i<n; i++) {
        if (obstacleGrid[i][0] == 1) break;
        dp[i][0] = 1;
    }
    for (int i=0; i<m; i++) {
        if (obstacleGrid[0][i] == 1) break;
        dp[0][i] = 1;
    }
    dp[0][0] = 1;

    for (int i=1; i<n; i++) {
        for (int j=1; j<m; j++) {
            if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
            else dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
}