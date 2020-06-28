#include <vector>
#include <string>
#include <iostream>

#include "../dfs_algs.h"

namespace dfs
{

bool dfs_exist(std::vector<std::vector<char>>& board, int x, int y, std::string& word, int index, std::vector<std::vector<bool>>& visited) {
    if (index == word.size()) return true;
    int direction[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (int i=0; i<4; i++) {
        int tmp_x = x + direction[i][0];
        int tmp_y = y + direction[i][1];
        if (tmp_x >=0 && tmp_x < board.size() && tmp_y >=0 && tmp_y < board[0].size() && visited[tmp_x][tmp_y] == false && board[tmp_x][tmp_y] == word[index]) {
            visited[tmp_x][tmp_y] = true;
            if (dfs_exist(board, tmp_x, tmp_y, word, index+1, visited)) {
                return true;
            }
            visited[tmp_x][tmp_y] = false;
        }
    }
    return false;
}

bool exist(std::vector<std::vector<char>>& board, std::string word) {
    std::vector<std::vector<bool>> visited(board.size(), std::vector<bool>(board[0].size(), false));
    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[i].size(); j++) {
            if (board[i][j] != word[0]) continue;
            visited[i][j] = true;
            if (dfs_exist(board, i, j, word, 1, visited)) {
                return true;
            }
            visited[i][j] = false;
        }
    }
    return false;
}

} // namespace dfs
