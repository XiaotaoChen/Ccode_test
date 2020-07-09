#include <string>
#include <stack>
#include "../stack_algs.h"

namespace stack_algs
{

int longestValidParentheses_v4(std::string s) {
    if (s.length() <2) return 0;
    std::stack<int> st;
    int n = s.length();
    int dp[n];
    std::fill_n(dp, n, 0);
    int result = 0;
    for (int i=0; i<n; i++) {
        if (s[i]=='(') st.push(i);
        else {
            if (!st.empty()) {
                int idx = st.top();
                st.pop();
                if (idx==0) dp[i] = i - idx + 1;
                else dp[i] = i - idx + 1 + dp[idx-1];
                result = result > dp[i] ? result : dp[i];
            }
        }
    }
    return result;
}

} // namespace stack_algs
