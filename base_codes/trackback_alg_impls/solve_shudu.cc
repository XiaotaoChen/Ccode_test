#include <vector>

#include "../trace_back_algs.h"


bool track_back::is_legal(std::vector<std::vector<char>>& board, int x, int y) {
    char curr = board[x][y];
    for (int i=0; i<9; i++) {
        // row check
        if (i != y && board[x][i] == curr) return false;
        // col check
        if (i != x && board[i][y] == curr) return false;
    }
    // sub matrix check
    int sub_x_start = (x / 3) * 3;
    int sub_y_start = (y / 3) * 3;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (sub_x_start+i == x && sub_y_start+j == y) continue;
            if (board[sub_x_start + i][sub_y_start + j] == curr) return false;
        }
    }
    return true;
}

bool track_back::track_back_solveSudoku(std::vector<std::vector<char>>& board, int x, int y) {
    if (x>8 || y>8) return true;
    if (board[x][y] != '.') {
        if (y < 8){
                return track_back_solveSudoku(board, x, y+1);
        }
        else {
            return track_back_solveSudoku(board, x+1, 0);
        }
    }

    bool flag = false;
    for (int i=1; i<10; i++) {
        char tmp = '0' + i;
        board[x][y]=tmp;
        if (is_legal(board, x, y)) {
            if (y < 8){
                flag = track_back_solveSudoku(board, x, y+1);
            }
            else {
                flag = track_back_solveSudoku(board, x+1, 0);
            }
            if (flag) return flag;
            else board[x][y] = '.';
        }
        else {
            board[x][y] = '.';
        }
    }
    return false;
}

void track_back::solveSudoku(std::vector<std::vector<char>>& board) {
    track_back_solveSudoku(board, 0, 0);
}

bool track_back::track_back_solveSudoku_v2(std::vector<std::vector<char>>& board, int x, int y, 
                               std::vector<std::vector<bool>> & rows, 
                               std::vector<std::vector<bool>> & cols,
                               std::vector<std::vector<bool>> & boxs) {
    if (x==board.size()) return true;
    if (y==board[0].size()) return track_back_solveSudoku_v2(board, x+1, 0, rows, cols, boxs);
    if (board[x][y]!='.') return track_back_solveSudoku_v2(board, x, y+1, rows, cols, boxs);
    for (int i=0; i<9; i++) {
        if (rows[x][i]==false && cols[y][i]==false && boxs[(x/3)*3+y/3][i]==false) {
            board[x][y] = i+'1';
            rows[x][i]=true; cols[y][i]=true; boxs[(x/3)*3 + y/3][i]=true;
            bool flag = track_back_solveSudoku_v2(board, x, y+1, rows, cols, boxs);
            if (flag) return true;
            board[x][y] = '.';
            rows[x][i]=false; cols[y][i]=false; boxs[(x/3)*3 + y/3][i]=false;
        }
    }
    return false;
}

void track_back::solveSudoku_v2(std::vector<std::vector<char>>& board) {
    if (board.size()!=9|| board[0].size()!=9) return;
    std::vector<std::vector<bool>> rows(9, std::vector<bool>(9, false));
    std::vector<std::vector<bool>> cols(9, std::vector<bool>(9, false));
    std::vector<std::vector<bool>> boxs(9, std::vector<bool>(9, false));

    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[i].size(); j++) {
            if (board[i][j]!='.') {
                int val = board[i][j] - '1';
                rows[i][val] = true;
                cols[j][val] = true;
                boxs[(i/3)*3 + j/3][val] = true;
            }
        }
    }
    track_back_solveSudoku_v2(board, 0, 0, rows, cols, boxs);
}
