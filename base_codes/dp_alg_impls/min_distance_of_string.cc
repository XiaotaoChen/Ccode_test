#include<string>
#include<cstdio>

#include "../dp_algs.h"

int dp::min_distance_of_str(std::string S, std::string T) {
    int s_len = S.length();
    int t_len = T.length();
    if (s_len < t_len ) return 0;
    int dp[s_len+1][t_len+1];
    std::fill_n(dp[0], (s_len+1) * (t_len+1), 0);
    for (int i=0; i< s_len + 1; i++) dp[i][0] = 1;
    for (int i=0; i < s_len; i++) {
        for(int j=0; j < t_len && j<=i; j++) {
            dp[i+1][j+1] = dp[i][j+1];
            if (S[i] == T[j]) dp[i+1][j+1] += dp[i][j];
        }
    }
    return dp[s_len][t_len];
}