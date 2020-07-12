#include <vector>
#include <stack>
#include "../hot_100.h"

namespace hot_100
{

std::vector<int> dailyTemperatures(std::vector<int>& T) {
    if (T.size() ==0) return {};
    int n = T.size();
    std::vector<int> result(n, 0);
    std::stack<int> st;
    for (int i=0; i<n; i++) {
        while (!st.empty() && T[i] > T[st.top()]) {
            int pre_idx = st.top(); st.pop();
            result[pre_idx] = i - pre_idx;
        }
        st.push(i);
    }
    return result;
}

} // namespace hot_100
