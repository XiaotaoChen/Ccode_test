#include<string>
#include<vector>

#include "../greedy_algs.h"


bool greedy::isMatch(std::string s, std::string p) {
    if (s.size() == 0) {
        if (p.size() ==0) return true;
        for (int i=0; i<p.size(); i++) if (p[i]!='*') return false;
        return true;
    }
    if (p.size() == 0) return false;

    int n = s.size();
    int m = p.size();
    bool dp[n+1][m+1];
    std::fill_n(dp[0], (n+1)*(m+1), false);
    dp[0][0] = true;
    // set dp[0][i] value
    for (int i=0; i<p.size(); i++) {
        if (p[i] == '*') dp[0][i+1] = true;
        else break;
    }
    

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (p[j]==s[i] || p[j] == '?') {
                dp[i+1][j+1] = dp[i][j];
            }
            else if (p[j] == '*') {
                int k=i+1;
                while(k>=0) {
                    if (dp[k][j]) {
                        dp[i+1][j+1] = true;
                        break;
                    }
                    k--;
                }
            }
        }
    }

    return dp[n][m];
}