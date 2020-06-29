#include <vector>
#include <stack>
#include "../stack_algs.h"

namespace stack_algs
{

int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    if (matrix.size()==0 || matrix[0].size()==0) return 0;
    int n = matrix.size();
    int m = matrix[0].size();
    std::vector<int> heights(m, 0);
    int result = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            heights[j] = matrix[i][j]=='0' ? 0: heights[j]+1;
        }
        int curr_area = largestRectangleArea(heights);
        result = result > curr_area ? result : curr_area;
    }
    return result;
}

} // namespace stack_algs