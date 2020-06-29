#include <vector>
#include <stack>
#include "../stack_algs.h"

namespace stack_algs
{

int largestRectangleArea(std::vector<int>& heights) {
    if (heights.size()==0) return 0;
    if (heights.size()==1) return heights[0];
    // save index
    std::stack<int> st;
    int result = INT32_MIN;
    for (int i=0; i<heights.size(); i++) {
        if (st.empty() || heights[st.top()] < heights[i]) {
            st.push(i);
        }
        else {
            while(!st.empty() && heights[st.top()] >= heights[i]) {
                int curr_idx = st.top();st.pop();
                int curr_h = heights[curr_idx];
                int area = 0;
                if (!st.empty()) {
                    area = (i - st.top()-1) * curr_h;
                }
                else {
                    area = i * curr_h;
                }
                result = result > area ? result:area;
            }
            st.push(i);
        }
    }

    int len = heights.size();
    while(!st.empty()) {
        int curr_idx = st.top(); st.pop();
        int curr_h = heights[curr_idx];
        int area = 0;
        if (!st.empty()) {
            area = (len - st.top() - 1) * curr_h;
        }
        else {
            area = len * curr_h;
        }
        result = result > area ? result : area;
    }
    return result;
}

} // namespace stack_algs
