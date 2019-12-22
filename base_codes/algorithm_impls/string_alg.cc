#include <stack>
#include "../algorithm.h"



vector<string> generate_parentheses(int n) {
    bool visited[2 * n];
    char parentheses[2 * n];
    char correct_p[2 * n];
    for (int i =0 ; i< n; i++) {
        visited[i] = false;
        visited[i+n] = false;
        parentheses[i] = '(';
        parentheses[i + n] = ')';
    }
    vector<string> results;
    generate_parentheses_dfs(0, 2 * n, visited, correct_p, parentheses, results);
    return results;
}

bool isOk(char tmp_p[], int n){
    std::stack<char> s;
    for (int i=1 ; i < n; i++) {
        if (tmp_p[i] == '(') {
            s.push('(');
        }
        else {
            if (!s.empty()) s.pop();
            else return false;
        }
    }
    return true;
}

void generate_parentheses_dfs(int depth, int num, bool visited[], char correct_p[], char parentheses[], 
                              vector<string>& results) {
    if (depth == num) {
        results.push_back(string(correct_p));
        return;
    }
    if (isOk(correct_p, depth)) {
        for (int i=0; i < num; i++) {
            if (visited[i] == false) {
                correct_p[depth] = parentheses[i];
                visited[i] = true;
                generate_parentheses_dfs(depth+1, num, visited, correct_p, parentheses);
                visited[i] = false;
            }
        }
    }
    else return;
}


