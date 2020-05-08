#include <vector>
#include<iostream>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void clockwise_print(std::vector<std::vector<int>>& matrix) {
    if (matrix.size() == 0) return;

    int row = matrix.size();
    int col = matrix[0].size();

    int ring = row < col ? row/2 : col/2;
    for (int i=0; i<=ring; i++) {
        int right_down_row = row - i - 1;
        int right_down_col = col - i - 1;

        // left to right
        for (int j = i; j<=right_down_col; j++) std::cout << matrix[i][j] << " ";
        // top to down
        if (i >= right_down_row) return; // 右下角的行数要大于左上角的行数
        for (int j=i+1; j<=right_down_row; j++) std::cout << matrix[j][right_down_col] << " ";
        // right to left
        if (i >=right_down_col) return; // 右下角的列数要大于左上角的列数
        for (int j=right_down_col -1; j>=i; j--) std::cout << matrix[right_down_row][j] << " ";
        // down to top
        for (int j=right_down_row-1; j>i; j--) std::cout << matrix[j][i] << " ";
        std::cout << std::endl;
    }
}

} // namespace sword_finger_offer
