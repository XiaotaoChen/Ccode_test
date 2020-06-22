#include <vector>
#include <stack>
#include <algorithm>
#include "../stack_algs.h"

namespace stack_algs
{

int trap_v2(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    int result = 0;
    std::stack<int> st;

    for (int i=0; i < height.size(); i++) {
        if (st.empty() || height[i] < height[st.top()]) {
            st.push(i);
        }
        else {
            while (!st.empty() &&  height[i] >= height[st.top()]) {
                int bottom = st.top(); st.pop();
                if (st.empty()) break;
                int left = st.top();
                int min_height = std::min(height[i], height[left]);
                int area = (i - left -1) * (min_height - height[bottom]);
                result += area;
            }
            st.push(i);
        }
    }
    return result;
}

} // namespace stack_algs
