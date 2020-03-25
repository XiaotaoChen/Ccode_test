#include <vector>
#include "../geometric_algs.h"

namespace geometric_alg
{

int surfaceArea(std::vector<std::vector<int>>& grid) {
    if (grid.size()==0) return 0;
    int row = grid.size();
    int col = grid[0].size();
    int result = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (grid[i][j] > 0) {
                result +=2;
                for (int k=0; k<4; k++) {
                    int neig_x = i + directions[k][0];
                    int neig_y = j + directions[k][1];
                    if (neig_x >=0 && neig_x <row && neig_y>=0 && neig_y<col) {
                        if (grid[i][j]>grid[neig_x][neig_y]) {
                            result += grid[i][j] - grid[neig_x][neig_y];
                        }
                    }
                    else {
                        result += grid[i][j];
                    }
                }
            }
        }
    }
    return result;
}

} // namespace geometric_alg
