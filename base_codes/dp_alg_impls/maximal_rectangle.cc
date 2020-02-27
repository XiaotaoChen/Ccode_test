#include <vector>
#include <stack>

#include "../dp_algs.h"

int dp::max_rectangle(std::vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;
    int result = 0;
    std::stack<int> s;
    s.push(0);
    for (int i=1; i<n; i++) {
        if (!s.empty() && heights[s.top()] < heights[i]) {
            s.push(i);
        }
        else {
            int curr = 0;
            while(!s.empty() && heights[s.top()] >= heights[i]) {
                int idx = s.top();
                s.pop();
                int left = !s.empty()? s.top()+1:0;
                curr = (i - left) * heights[idx];
                result = result > curr? result:curr;
            }
            s.push(i);
        }
    }
    
    while(!s.empty()) {
        int idx = s.top();
        s.pop();
        int left = !s.empty()? s.top()+1:0;
        int curr = (n - left) * heights[idx];
        result = result > curr ? result : curr;
    }
    return result;
}

int dp::maximalRectangle(std::vector<std::vector<char>>& matrix) {
    int n = matrix.size();
    if (n == 0) return 0;
    int m = matrix[0].size();
    if (m==0) return 0;

    std::vector<int> heights(m, 0);
    int result = 0;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (matrix[i][j] == '1') {
                heights[j] ++;
            }
            else {
                heights[j] = 0;
            }
        }
        int curr = max_rectangle(heights);
        result = result > curr ? result : curr;
    }
    return result;
}