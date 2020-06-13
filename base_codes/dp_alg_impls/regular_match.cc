#include <cstdio>
#include <string>
#include <iostream>

#include "../dp_algs.h"

bool dp::isLegal(char normal, char match) {
    if (match == '.' || normal == match) return true;
    return false;
}

bool dp::regular_match(std::string s, std::string p) {
    int s_len = s.length();
    int p_len = p.length();
    bool dp[s_len+1][p_len+1];
    std::fill_n(dp[0], (s_len + 1) *(p_len + 1), false);
    dp[0][0]=true;
    
    // for 0 match '', 'c*'
    for(int i=0; i<p_len; i++) {
        if (p[i] == '*') dp[0][i+1] = dp[0][i-1];
    }

    for (int i=0; i<s_len; i++) {
        for(int j=0; j<p_len; j++) {
            if (p[j] != '*') {
                if (isLegal(s[i], p[j])) {
                    dp[i+1][j+1] = dp[i][j]; 
                }
            }
            else {
                // match 0 number 'a', 'c*a'
                dp[i+1][j+1] = dp[i+1][j-1];
                // match >=1 number
                int curr_idx = i;
                while(curr_idx >=0 &&isLegal(s[curr_idx], p[j-1])) {
                    // dp[i,j]=dp[i-1][j-1]
                    if (dp[curr_idx][j-1] == true) {
                        dp[i+1][j+1] = true;
                        break;
                    }
                    curr_idx--;
                }
            }
        }
    }
    return dp[s_len][p_len];
}

bool dp::regular_match_v2(std::string& s, std::string &p) {
    int slen = s.length();
    int plen = p.length();
    if (slen==0 && plen==0) return true;
    // if (plen==0|| (slen==0 && p[1]!='*')) return false;

    bool dp[slen + 1][plen + 1];
    std::fill_n(dp[0], (slen+1)* (plen+1), false);
    dp[0][0] = true;
    for (int i=2; i<=plen; i+=2) {
        if (p[i-1]=='*') dp[0][i]=dp[0][i-2];
    }


    for (int i=1; i<=slen; i++) {
        for (int j=1; j<= plen; j++) {
            if (p[j-1]!='*') {
                if (s[i-1]==p[j-1] || p[j-1]=='.') {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = false;
                }
            }
            else {
                // match 0
                dp[i][j] = dp[i][j-2];
                if (dp[i][j]) continue;
                // match >=1
                int idx = i;
                while(idx>0 && (s[idx-1]==p[j-2] || p[j-2]=='.')) {
                    if (dp[idx][j-1]) {
                        dp[i][j] = true;
                        break;
                    }
                    idx--;
                }
            }
        }
    }
    return dp[slen][plen];
}