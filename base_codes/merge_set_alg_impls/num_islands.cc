#include <vector>
#include <stack>

#include "../merge_set.h"


int merge_set::numIslands(std::vector<std::vector<char>>& grid) {
    int row = grid.size();
    if (row==0) return 0;
    int col = grid[0].size();
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));

    std::vector<std::vector<int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    std::stack<std::pair<int, int>> s;

    int count = 0;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (visited[i][j] || grid[i][j]=='0') continue;
            if (grid[i][j]=='1') {
                count++;
                s.push({i,j});
                while(!s.empty()) {
                    std::pair<int, int> pair = s.top(); s.pop();
                    int x = pair.first;
                    int y = pair.second;
                    visited[x][y] = true;
                    for (int i=0; i<directions.size(); i++){
                        int curr_x = x+directions[i][0];
                        int curr_y = y+directions[i][1];
                        if (curr_x>=0 && curr_x<row && curr_y>=0 && curr_y<col &&
                            visited[curr_x][curr_y] == false && grid[curr_x][curr_y]=='1') {
                                s.push({curr_x, curr_y});
                            }
                    }
                }
            }
        }
    }
    return count;
}
