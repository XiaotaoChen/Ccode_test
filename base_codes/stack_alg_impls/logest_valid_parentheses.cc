#include <vector>
#include <stack>

#include "../stack_algs.h"

int stack_algs::longestValidParentheses(std::string s) {
    if (s.length()<2) return 0;
    int n = s.length();
    int lens[n];
    std::fill_n(lens, n, 0);

    int result = 0;
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
        }
    }
    return result;
}

int stack_algs::longestValidParentheses_v2(std::string s) {
    if (s.length()<2) return 0;
    std::stack<int> st;
    int result = 0;
    st.push(-1);
    for(int i=0; i<s.length(); i++) {
        if (s[i]=='(') st.push(i);
        else {  // st中不会存在'))'这种情况，
            st.pop(); // pop "("
            if (st.empty()) { // 左右括号已完全匹配，）是多余的，push到栈中，作为下标。
                st.push(i);
            }
            else {
                result = result > (i - st.top()) ? result: (i - st.top());
            }
        }
    }
    return result;
}

int stack_algs::longestValidParentheses_v3(std::string s) {
    int len = s.length();
    if (len <2) return 0;
    std::stack<int> st;

    int result = 0;
    int tmp[len];
    std::fill_n(tmp, len, 0);

    for (int i=0; i<len; i++) {
        if (s[i] == '(' ) {
            st.push(i);
        }
        else {
            if (!st.empty() && s[st.top()] =='(') {
                tmp[i] = i - st.top() +1;
                st.pop();
                if (i - tmp[i] >=0) tmp[i] += tmp[i - tmp[i]];
                result = result > tmp[i] ? result: tmp[i];
            }
        }
    }
    return result;
}