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