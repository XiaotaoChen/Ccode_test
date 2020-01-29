#include "../algorithm.h"

void dfs(vector<vector<char> >& board, 
         vector<vector<bool> >& visited, 
         int x, 
         int y) {
    int width = board.size();
    int height = board[0].size();
    if(x>=0 && x < width && y>=0 && y < height) {
        if(visited[x][y] == true) return;
        visited[x][y] = true;
        if (board[x][y] == 'O') {
            board[x][y] = '*';
            static int directions[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            for(int i=0; i<4; i++) {
                dfs(board, visited, x+directions[i][0], y+directions[i][1]);
            }
        }
    }
}

void SurroundingReigon(vector<vector<char> >& board) {
    if (board.size() == 0) return;
    int width = board.size();
    int length = board[0].size();
    vector<vector<bool> > visited(width);
    for (int i=0; i<width; i++)
        for(int j=0; j<length; j++)
            visited[i].push_back(false);
    for(int i=0;i<width; i++){
        dfs(board, visited, i, 0);
        dfs(board, visited, i, length-1);
    }
    for (int i=0;i<length; i++) {
        dfs(board, visited, 0, i);
        dfs(board, visited, width-1, i);
    }

    for(int i=0; i<width; i++) {
        for(int j=0; j<length; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
        }
    }

    for(int i=0; i<width; i++) {
        for(int j=0; j<length; j++) {
            if (board[i][j] == '*') board[i][j] = 'O';
        }
    }
    return;
}