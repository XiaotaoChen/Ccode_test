#include <stack>
#include "../algorithm.h"

int reverse_polish_notation(vector<string> &tokens){
    if (tokens.size() == 0) return 0;
    std::stack<int> s;
    for (int i=0; i < tokens.size(); i++) {
        if (tokens[i] == "+" || tokens[i] == "-" 
            || tokens[i] == "*" || tokens[i] == "/") {
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                int result = 0;
                if (tokens[i] == "+") s.push(a + b);
                else if (tokens[i] == "-") s.push(a - b);
                else if (tokens[i] == "*") s.push(a * b);
                else s.push(a / b);
            }
        else {
            int tmp = stoi(tokens[i]);
            s.push(tmp);
        }
    }
    return s.top();
}