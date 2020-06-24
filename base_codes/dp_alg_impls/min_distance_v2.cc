#include <vector>
#include <algorithm>

#include "../dp_algs.h"

namespace dp
{

int minDistance_v2(std::string& word1, std::string& word2) {
    if (word1.length()==0) return word2.length();
    if (word2.length()==0) return word1.length();
    int m = word1.length();
    int n = word2.length();
    int dp_arr[m+1][n+1];
    std::fill_n(dp_arr[0], (m+1) * (n+1), 0);
    for (int i=1; i<=m; i++) dp_arr[i][0] = i;
    for (int i=1; i<=n; i++) dp_arr[0][i] = i;
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (word1[i-1]==word2[j-1]) dp_arr[i][j] = dp_arr[i-1][j-1];
            else {
                dp_arr[i][j] = std::min(std::min(dp_arr[i-1][j-1], dp_arr[i-1][j]), dp_arr[i][j-1]) +1;
            }
        }
    }
    return dp_arr[m][n];
}

} // namespace dp
