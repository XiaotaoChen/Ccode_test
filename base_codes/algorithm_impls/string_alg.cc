#include <stack>
#include "../algorithm.h"

bool isOk(char tmp_p[], int n){
    std::stack<char> s;
    for (int i=0 ; i < n; i++) {
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
        string tmp = string(correct_p);
        for (int i=0; i < results.size(); i++) {
            if (results[i] == tmp) return;
        }
        results.push_back(tmp);
        return;
    }
    if (isOk(correct_p, depth)) {
        for (int i=0; i < num; i++) {
            if (visited[i] == false) {
                correct_p[depth] = parentheses[i];
                visited[i] = true;
                generate_parentheses_dfs(depth+1, num, visited, correct_p, parentheses, results);
                visited[i] = false;
            }
        }
    }
    else return;
}

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

void generate_parentheses_dfs(string curr_s, int num_left, int num_right, vector<string> & results){
    if (num_left == 0 && num_right == 0) results.push_back(curr_s);
    if (num_left > 0 && num_left <= num_right) generate_parentheses_dfs(curr_s+"(", num_left -1, num_right, results);
    if (num_right > 0 && num_left < num_right) generate_parentheses_dfs(curr_s+")", num_left, num_right -1, results);
}


vector<string> generate_parentheses2(int n) {
    vector<string> results;
    string tmp = "";
    generate_parentheses_dfs(tmp, 3, 3, results);
    return results;
}