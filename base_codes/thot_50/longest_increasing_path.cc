#include <vector>
#include <queue>

namespace thot_50
{

int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
    if (matrix.size()==0) return 0;
    int row = matrix.size();
    int col = matrix[0].size();
    if (row==1 && col ==1) return 1;
    int in_degrees[row][col];
    std::fill_n(in_degrees[0], row*col, 0);
    int directions[4][2] = {{0,1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            for (int k=0; k<4; k++) {
                int x = i + directions[k][0];
                int y = j + directions[k][1];
                if (x>=0 && x<row && y>=0 && y<col && matrix[i][j] > matrix[x][y]) {
                    in_degrees[i][j]++;
                }
            }
        }
    }

    std::queue<std::pair<int, int>> qu;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (in_degrees[i][j]==0) {
                qu.push({i, j});
            }
        }
    }

    int depth=0;
    while(!qu.empty()) {
        depth++;
        int size = qu.size();
        for (int i=0; i<size; i++) {
            std::pair<int, int> p = qu.front(); qu.pop();
            for (int j=0; j<4; j++) {
                int x = p.first + directions[j][0];
                int y = p.second + directions[j][1];
                if (x>=0 && x<row && y>=0 && y<col && matrix[x][y] > matrix[p.first][p.second]) {
                    in_degrees[x][y]--;
                    if (in_degrees[x][y]==0) qu.push({x, y});
                }
            }
        }
    }
    return depth;
}

} // namespace thot_50
