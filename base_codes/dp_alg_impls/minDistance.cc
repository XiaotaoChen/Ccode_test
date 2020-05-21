#include <string>
#include <algorithm>
#include "../dp_algs.h"

namespace dp
{

int minDistance(std::string& word1, std::string& word2) {
    if (word1.length()==0) return word2.length();
    if (word2.length()==0) return word1.length();

    int m = word1.length();
    int n = word2.length();
    int dp[m+1][n+1];
    for (int i=0; i<=m; i++) dp[i][0] = i;
    for (int i=1; i<=n; i++) dp[0][i] = i;

    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = std::min(std::min(dp[i-1][j], dp[i][j-1]) +1, dp[i-1][j-1]);
            }
            else {
                dp[i][j] = std::min(std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
            }
        }
    }
    return dp[m][n];
}

} // namespace dp
