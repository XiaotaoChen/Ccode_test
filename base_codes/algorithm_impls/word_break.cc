#include <cstring> // memset
#include <set>
#include "../algorithm.h"

bool wordBreak(string s, unordered_set<string> &dict) {
    int n = s.length();
    bool dp[n + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (int i=1; i<=n; i++) {
        for (int j=0; j< i; j++) {
            if (dp[j]) {
                string sub = s.substr(j, i - j);
                if (dict.find(sub) != dict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    return dp[n];
}

vector<string> wordBreak_v2(string s, unordered_set<string> &dict) {
    int n = s.length();
    bool dp[n + 1];
    vector<vector<string>> results = vector<vector<string>>(n+1);
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (int i=1; i<=n; i++) {
        for (int j=0; j< i; j++) {
            if (dp[j]) {
                string sub = s.substr(j, i - j);
                if (dict.find(sub) != dict.end()){
                    dp[i] = true;
                    if (j != 0) {
                        // copy dp[j] solutions to dp[i]
                        for (int idx=0; idx<results[j].size(); idx++) {
                            string tmp_str = results[j][idx] + " " + sub;
                            results[i].push_back(tmp_str);
                        }
                    } 
                    else{
                        results[i].push_back(sub);
                    }
                }
            }
        }
    }
    return results[n];
}

void wordBreakDFS(int idx, bool dp[], vector<vector<string>>& results, unordered_set<string>& dict, string s) {
    if (idx == 0) return;
    for (int i = idx-1; i>=0; i--) {
        if (dp[i]) {
            string sub = s.substr(i, idx - i);
            if (dict.find(sub) != dict.end()) {
                if (results[idx].size() == 0) {
                    // results[i].insert(sub);
                    results[i].push_back(sub);
                }
                else {
                    for (int tmp_i = 0; tmp_i < results[idx].size(); tmp_i++) {
                        string tmp = sub + " " + results[idx][tmp_i];
                        bool flag = false;
                        for(int kk = 0; kk < results[i].size(); kk++){
                            if (results[i][kk] == tmp) {
                                flag = true;
                                break;
                            }
                        }
                        if (!flag) {
                            results[i].push_back(tmp);
                        }
                    }
                    // for (std::set<string>::iterator it = results[idx].begin(); it != results[idx].end(); it++) {
                    //     string tmp = sub + " " + *it;
                    //     if (results[i].find(tmp) == results[i].end()) {
                    //         results[i].insert(tmp);
                    //     }
                    // }
                }
                wordBreakDFS(i, dp, results, dict, s);
            }
        }
    }
}

vector<string> wordBreak_v3(string s, unordered_set<string> &dict) {
    int n = s.length();
    bool dp[n + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (int i=1; i<=n; i++) {
        for (int j=0; j< i; j++) {
            if (dp[j]) {
                string sub = s.substr(j, i - j);
                if (dict.find(sub) != dict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    vector<vector<string>> results = vector<vector<string>>(n+1);
    wordBreakDFS(n, dp, results, dict, s);
    // // convert set to vector
    // vector<string> result0(results[0].begin(), results[0].end());
    return results[0];
}

