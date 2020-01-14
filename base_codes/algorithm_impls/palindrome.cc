#include <string>
#include "../algorithm.h"

bool is_palindrome(string& str) {
    return str == string(str.rbegin(), str.rend());
}

void dfs(string& str, vector<string>& curr, vector<vector<string> >& result) {
    if (str == "") {
        result.push_back(curr);
        return;
    }
    for (int i=1; i <= str.size(); i++) {
        string substr = str.substr(0, i);
        if (is_palindrome(substr)) {
            curr.push_back(substr);
            string tmp = str.substr(i);
            dfs(tmp, curr, result);
            curr.pop_back();
        }
    }
}

vector<vector<string> > palindrome_partition(string& str) {
    vector<vector<string> > result;
    vector<string> curr;
    dfs(str, curr, result);
    return result;
}