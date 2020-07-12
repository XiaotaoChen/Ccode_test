#include <vector>
#include "../hot_100.h"

namespace hot_100
{

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.size()==0 || matrix[0].size()==0) return false;
    int row = matrix.size();
    int col = matrix[0].size();
    if (matrix[0][0] > target || matrix[row-1][col-1] < target) return false;
    int row_idx = row-1;
    int col_idx = 0;
    while(row_idx >=0 && col_idx < col) {
        if (matrix[row_idx][col_idx] == target) return true;
        if (matrix[row_idx][col_idx] < target) col_idx++;
        else row_idx--;
    }
    return false;
}

} // namespace hot_100

