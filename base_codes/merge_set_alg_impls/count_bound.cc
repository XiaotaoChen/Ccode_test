#include<vector>
#include<stack>

#include "../merge_set.h"

void merge_set::solve(std::vector<std::vector<char>>& board) {
    int row = board.size();
    if (row==0) return;
    int col = board[0].size();

    std::stack<std::pair<int, int>> s;

    for (int i=0; i<col; i++) {
        if (board[0][i]=='O') s.push({0,i});
        if (board[row-1][i] == 'O') s.push({row-1, i});
    }
    for (int i=1; i<row-1; i++) {
        if (board[i][0]=='O') s.push({i, 0});
        if (board[i][col-1]=='O') s.push({i, col-1});
    }
    
    std::vector<std::vector<int>> directions={{-1,0},{1,0},{0,-1},{0,1}};

    // std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));

    int x, y;
    while(!s.empty()) {
        std::pair<int, int> pair = s.top(); s.pop();
        x = pair.first;
        y = pair.second;
        board[x][y] = 'A';
        for (int i=0; i<directions.size(); i++) {
            if (x+directions[i][0] >0 && x+directions[i][0]<row && 
                y+directions[i][1]>=0 && y+directions[i][1]<col && 
                board[x+directions[i][0]][y+directions[i][1]]=='O') {
                s.push({x+directions[i][0], y+directions[i][1]});
            }
        }
    }
    
    // set O to X, A->O
    for (int i=0; i<row; i++ ){
        for (int j=0; j<col; j++) {
            if (board[i][j]=='O') board[i][j] = 'X';
            else if (board[i][j]=='A') board[i][j] = 'O';
        }
    }
    return;
}