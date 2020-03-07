#include <vector>
#include <stack>

#include "../stack_algs.h"

int stack_algs::longestValidParentheses(std::string s) {
    if (s.length()<2) return 0;
    int n = s.length();
    int lens[n];
    std::fill_n(lens, n, 0);

    int result = 0;
    int curr = 0;
    std::stack<int> st;
    for (int i=0; i<n; i++) {
        if (s[i]=='(') st.push(i);
        else {
            if (!st.empty()) {
                int left_idx = st.top(); st.pop();
                lens[i] = i - left_idx + 1;
                if (left_idx>0) lens[i] += lens[left_idx-1];
                result = result > lens[i] ? result : lens[i];
            }
            else {
                curr = 0;
            }
        }
    }
    return result;
}