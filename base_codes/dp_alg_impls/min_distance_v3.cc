#include <vector>
#include <string>
#include "../dp_algs.h"

namespace dp
{

int minDistance_v3(std::string& word1, std::string& word2) {
    if (word1.length()==0) return word2.length();
    if (word2.length()==0) return word1.length();
    int n = word1.length();
    int m = word2.length();
    int dist[n+1][m+1];
    std::fill_n(dist[0], (n+1)*(m+1), 0);
    for (int i=1; i<=n;i++) dist[i][0] = i;
    for (int i=1; i<=m;i++) dist[0][i] = i;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (word1[i-1]==word2[j-1]) dist[i][j] = dist[i-1][j-1];
            else dist[i][j] = std::min(std::min(dist[i-1][j-1], dist[i-1][j]), dist[i][j-1]) + 1;
        }
    }
    return dist[n][m];
}

} // namespace dp
