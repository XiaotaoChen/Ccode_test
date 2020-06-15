#include <stack>
#include <string>
#include "../stack_algs.h"

namespace stack_algs
{

bool isright(char a, char b) {
    if (a == '(' && b == ')') return true;
    if (a == '[' && b == ']') return true;
    if (a == '{' && b == '}') return true;
    return false;
}

bool isValid_parentness(std::string& s) {
    if (s.length()==0) return true;
    if (s.length() < 2) return false;
    std::stack<char> st;
    for (int i=0; i<s.length(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            st.push(s[i]);
        }
        else {
            if (st.empty()) return false;
            if (!isright(st.top(), s[i]))  return false;
            st.pop();
        }
    }
    if (st.empty()) return true;
    return false;
}

} // namespace stack_algs
