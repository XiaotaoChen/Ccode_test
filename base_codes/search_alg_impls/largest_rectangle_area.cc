#include <cstdio>
#include <stack>
#include<vector>

#include "../search_algs.h"

int search::largestRectangleArea(std::vector<int>& heights) {
    if (heights.size() ==0) return 0;
    std::stack<int> s_idx;
    s_idx.push(0);

    int result = 0;
    int size = heights.size();

    for (int i=1; i<heights.size(); i++) {
        // int top_idx = s_idx.top();
        if (heights[i] > heights[s_idx.top()]) {
            s_idx.push(i);
        }
        else {
            while(!s_idx.empty() && heights[s_idx.top()] >=heights[i]) {
                int top_idx = s_idx.top();
                s_idx.pop();
                int left = !s_idx.empty() ? s_idx.top() + 1:0;
                int curr = (i - left) * heights[top_idx];
                result = result>curr ? result : curr;
            }
            s_idx.push(i);
        }
    }

    while(!s_idx.empty()) {
        int top_idx = s_idx.top();
        s_idx.pop();
        int left = !s_idx.empty() ? s_idx.top() + 1:0;
        int curr = (size - left) * heights[top_idx];
        result = result>curr ? result : curr;
    }

    return result;
}