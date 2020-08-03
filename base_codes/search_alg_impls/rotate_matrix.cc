#include <vector>
#include "../search_algs.h"

namespace search
{

void rotate(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n<=1) return;
    for (int i=0; i<n/2; i++) {
        for (int j=i; j<n-i-1; j++) {
            // rotate matrix without extra memory. 
            // (i,j) --> (j, n-i-1) --> (n-i-1, n-j-1) --> (n-j-1, i)
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[n-j-1][i];
            matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
            matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
            matrix[j][n-i-1] = tmp;
        }
    }
}

} // namespace search
