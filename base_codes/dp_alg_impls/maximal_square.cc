#include <cstdio>
#include <vector>

#include "../dp_algs.h"

int dp::maximalSquare(std::vector<std::vector<char>>& matrix) {
    if (matrix.size() == 0) return 0;
    int size1 = matrix.size();
    int size2 = matrix[0].size();
    int max_len = 0;
    int dp[size1][size2];
    std::fill_n(dp[0], size1 * size2, 0);
    for (int i=0; i<size1; i++) {
        if (matrix[i][0] == '1') {
            dp[i][0] = 1;
            max_len = 1;
        }
    }
    for (int i=0; i<size2; i++) {
        if (matrix[0][i] == '1') {
            dp[0][i] = 1;
            max_len = 1;
        }
    }
    for (int i=1; i<size1; i++) {
        for (int j=1; j< size2; j++) {
            if (matrix[i][j] == '1') {
                dp[i][j] = std::min(std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                max_len = max_len > dp[i][j]? max_len: dp[i][j];
            }
        }
    }
    return max_len * max_len;
}