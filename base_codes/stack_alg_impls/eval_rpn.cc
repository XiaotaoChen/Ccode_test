#include <vector>
#include <string>
#include <stack>

#include "../stack_algs.h"

int stack_algs::strToint(std::string str) {
    bool positive = true;
    int result = 0;
    for (int i=0; i<str.size(); i++) {
        if (i==0 && (str[i] == '-' || str[i] == '+')) {
            if (str[i]=='-') positive = false;
            continue;
        }
        result = result * 10 + (str[i] - '0');
    }
    if (!positive) return -result;
    return result;
}

int stack_algs::op_maps(int a, int b, char op_type) {
    int result = -1;
    switch (op_type)
    {
    case '+':
        result =  a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result =  a * b;
        break;
    case '/':
        result = a / b;
        break;
    default:
        break;
    }
    return result;
}

int stack_algs::evalRPN(std::vector<std::string>& tokens) {
    int n = tokens.size();
    if (n==0) return 0;
    if (n==1) return strToint(tokens[0]);
    std::stack<int> s;
    s.push(strToint(tokens[0]));
    
    for (int i=1;i<tokens.size(); i++) {
        if (tokens[i].length()==1 && (tokens[i][0] == '+' || tokens[i][0] == '-' || tokens[i][0] == '*' || tokens[i][0] == '/')) {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            s.push(op_maps(a, b, tokens[i][0]));
        }
        else {
            s.push(strToint(tokens[i]));
        }
    }
    return s.top();
}