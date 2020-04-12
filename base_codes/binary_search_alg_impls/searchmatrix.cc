#include <vector>
#include <cmath>
#include "../binary_search.h"

namespace binary_search
{

bool dfs_searchmatrix(std::vector<std::vector<int>>& matrix, int start, int end, int target) {
    if (start > end) return false;
    int row, col;
    if (start==end) {
        row = start / matrix[0].size();
        col = start % matrix[0].size();
        if (matrix[row][col] == target) return true;
        return false;
    }
    int mid = (start + end) / 2;
    row = mid / matrix[0].size();
    col = mid % matrix[0].size();
    if (matrix[row][col] == target) return true;
    if (matrix[row][col] < target) {
        return dfs_searchmatrix(matrix, mid+1, end, target);
    }
    else {
        return dfs_searchmatrix(matrix, start, mid-1, target);
    }
}

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.size()==0 || matrix[0].size()==0) return false;
    return dfs_searchmatrix(matrix, 0, matrix.size() * matrix[0].size() -1, target);
}

int kthsmallest_cnt(std::vector<std::vector<int>> & matrix, int val) {
    int i = matrix.size() - 1, j = 0, cnt = 0;
    while(i >=0 && j < matrix[0].size()) {
        if (matrix[i][j] <= val) {
            cnt += i + 1;
            j++;
        }
        else {
            i--;
        }
    }
    return cnt;
}

int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
    if (matrix.size()==0) return -1;
    if (k==1) return matrix[0][0];
    int left = matrix[0][0], right = matrix.back().back();
    while(left < right) {
        int mid = (left+right) /2;
        int cnt = kthsmallest_cnt(matrix, mid);
        if (cnt < k) left = mid+1;
        else right = mid;
    }
    return left;
}

} // namespace binary_search

