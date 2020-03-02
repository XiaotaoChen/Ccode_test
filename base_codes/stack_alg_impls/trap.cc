#include <vector>
#include <stack>

#include "../stack_algs.h"

int stack_algs::trap(std::vector<int>& height) {
    int n = height.size();
    if (n < 3) return 0;
    
    std::stack<int> s;
    s.push(0);
    
    int result = 0;

    for (int i=1; i<height.size(); i++) {
        if (height[i] < height[s.top()]) {
            s.push(i);
        }
        else {
            while (!s.empty() && height[s.top()] <= height[i]) {
                int low_idx = s.top(); s.pop();
                if (!s.empty()) {
                    int left_idx = s.top();
                    result += (i - left_idx - 1) * (std::min(height[i], height[left_idx]) - height[low_idx]);
                }
            }
            s.push(i);
        }
    }
    return result;
}
