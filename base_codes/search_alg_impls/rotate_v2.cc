#include <vector>
#include "../search_algs.h"

namespace search
{

void rotate_v2(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n<2) return;
    int n_1 = n-1;
    for (int i=0; i<n/2; i++) {
        for (int j=i; j<n-i-1; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[n_1-j][i];
            matrix[n_1-j][i] = matrix[n_1-i][n_1-j];
            matrix[n_1-i][n_1-j] = matrix[j][n_1-i];
            matrix[j][n_1-i] = tmp;
        }
    }
}

} // namespace search
