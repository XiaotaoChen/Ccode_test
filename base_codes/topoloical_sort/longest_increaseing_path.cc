#include <vector>
#include <queue>

#include "../topoloical_sort.h"

int topoloical_sort::longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
    int row = matrix.size();
    if(row==0) return 0;
    int col = matrix[0].size();
    if (row==1 && col==1) return 1;

    int in_degrees[row][col];
    // int dp[row][col];
    std::fill_n(in_degrees[0], row*col, 0);
    // std::fill_n(dp[0], row*col, 1);
    int directions[4][2] = {{0,1}, {0,-1},{1,0},{-1,0}};

    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            for (int k=0; k<4; k++) {
                int x = i + directions[k][0];
                int y = j + directions[k][1];
                if (x>=0 && x<row && y>=0 && y<col && matrix[i][j]>matrix[x][y]) in_degrees[i][j]++;
            }
        }
    }

    std::queue<std::pair<int, int>> q;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (in_degrees[i][j]==0) q.push({i,j});
        }
    }

    int depth=0;
    while(!q.empty()) {
        depth++;
        int curr_size = q.size();
        for (int i=0; i<curr_size; i++) {
            std::pair<int, int> p = q.front(); q.pop();
            for (int k=0; k<4; k++) {
                int x = p.first + directions[k][0];
                int y = p.second + directions[k][1];
                if (x>=0 && x<row && y>=0 && y<col && matrix[p.first][p.second] < matrix[x][y]) {
                    in_degrees[x][y]--;
                    // dp[x][y] = std::max(dp[x][y], dp[p.first][p.second]+1);
                    if (in_degrees[x][y]==0) q.push({x, y});
                }
            }
        }
    }
    return depth;
}