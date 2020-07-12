#include <vector>
#include <stack>
#include "../hot_100.h"

namespace hot_100
{


int findUnsortedSubarray(std::vector<int>& nums) {
    std::stack<int> st;
    int l = nums.size() - 1;
    int r = 0;
    for (int i = 0; i < nums.size(); i++) {
        while (!st.empty() && nums[st.top()] > nums[i]) {
            l = std::min(l, st.top());
            st.pop();
        }
        st.push(i);
    }
    st = std::stack<int>();
    for (int i = nums.size() - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            r = std::max(r, st.top());
            st.pop();
        }
        st.push(i);
    }
    return (r > l) ? r - l + 1 : 0;
}


} // namespace hot_100
