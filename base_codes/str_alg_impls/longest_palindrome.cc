#include<string>
#include "../str_algs.h"


std::string str_alg::longestPalindrome(std::string s) {
    std::string result = "";
    int curr_len = 0;
    for (int i=0; i<s.length(); i++) {
        int left = i;
        int right = i;
        // aba type
        while(left>=0 && right<s.length() && s[left]==s[right]) {
            left--;
            right++;
        }
        if (curr_len<(right-left-1)) {
            result = s.substr(left+1, right-left-1);
            curr_len = result.length();
        }
        // a|a type
        left = i;
        right = i+1;
        while(left>=0 && right<s.length() && s[left]==s[right]) {
            left--;
            right++;
        }
        if (curr_len<(right-left-1)) {
            result = s.substr(left+1, right-left-1);
            curr_len = right-left-1;
        }
    }
    return result;
}

std::string str_alg::longestPalindrome_dp(std::string s) {
    if (s.length()<2) return s;
    int len = s.length();
    bool dp[len][len];
    std::fill_n(dp[0],len*len, false);
    for (int i=0; i<len; i++) dp[i][i]=true;
    
    int left=0;
    int right = 0;
    for (int i=len-1; i>=0;i--) {
        for (int j=i+1; j<len; j++) {
            if (s[i]==s[j] && (j-i<3||dp[i+1][j-1])) {
                dp[i][j]=true;
                if (j-i+1>(right-left+1)) {
                    right = j;
                    left = i;
                }
            }
        }
    }
    return s.substr(left, right-left+1);
}