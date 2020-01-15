#include <string>
#include <climits>  // INT_MAX
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


void dfs(string& str, int& curr_cut, int& min_cut) {
    if (str == "") {
        min_cut = curr_cut < min_cut ? curr_cut : min_cut;
        return;
    }
    for (int i=1; i <= str.size(); i++) {
        string substr = str.substr(0, i);
        if (is_palindrome(substr)) {
            string tmp = str.substr(i);
            curr_cut++;
            dfs(tmp, curr_cut, min_cut);
            curr_cut--;
        }
    }
}

int palindrome_minCut(string& str) {
    if (str.length() == 0) return 0;
    int min_cut = str.length();
    int curr_cut = 0;
    dfs(str, curr_cut, min_cut);
    return min_cut - 1;
}

int palindrome_minCut_v2(string& str) {
    if (str.length()==0 || str.length()==1) return 0;
    int len = str.length();
    int dp[len+1];
    fill_n(dp, len+1, INT_MAX);
    dp[0] = 0;
    for (int i=1; i <= len; i++) {
        for (int j=0; j <i; j++) {
            if (dp[j] == INT_MAX) continue;
            string substr = str.substr(j, i-j);
            if (is_palindrome(substr)) {
                dp[i] = dp[j] + 1 < dp[i] ? dp[j] + 1 : dp[i];
            }
        }
    }
    return dp[len] - 1;
}