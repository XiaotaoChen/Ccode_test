#include <vector>

#include "../dp_algs.h"

namespace dp
{

int minPathSum(std::vector<std::vector<int>>& grid) {
    if (grid.size()==0) return 0;
    int m = grid.size();
    int n = grid[0].size();
    int dp_arr[m][n];
    std::fill_n(dp_arr[0], m*n, 0);
    dp_arr[0][0] = grid[0][0];
    for (int i=1; i<m; i++) dp_arr[i][0] = grid[i][0] + dp_arr[i-1][0];
    for (int i=1; i<n; i++) dp_arr[0][i] = grid[0][i] + dp_arr[0][i-1];

    for (int i=1; i<m; i++) {
        for (int j=1; j<n; j++) {
            dp_arr[i][j] = dp_arr[i-1][j] < dp_arr[i][j-1] ? dp_arr[i-1][j] : dp_arr[i][j-1];
            dp_arr[i][j] += grid[i][j];
        }
    }
    return dp_arr[m-1][n-1];
}

} // namespace dp
