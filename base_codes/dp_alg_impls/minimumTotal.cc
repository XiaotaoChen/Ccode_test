#include <cstdio>
#include <vector>
#include <climits> // INT_MAX
#include "../dp_algs.h"

int dp::minimumTotal(std::vector<std::vector<int> > &triangle) {
    int len = triangle.size();
    if (len==0) return 0;
    if (len==1) triangle[0][0];
    int dp[2][len];
    std::fill_n(dp[0], len*2, INT_MAX);
    dp[0][0]=triangle[0][0];
    for (int i=1; i<len; i++) {
        for(int j=0; j<=i; j++) {
            if (j==0) {
                dp[i%2][j] = dp[(i-1)%2][j] + triangle[i][j];
            }
            else if (j==i) {
                dp[i%2][j] = dp[(i-1)%2][j-1] + triangle[i][j];
            }
            else {
                dp[i%2][j] = std::min(dp[(i-1)%2][j], dp[(i-1)%2][j-1]) + triangle[i][j];
            }
        }
    }
    int line = (len-1)%2;
    int result = INT_MAX;
    for (int i=0; i<len; i++) result = std::min(result, dp[line][i]);
    return result;
}