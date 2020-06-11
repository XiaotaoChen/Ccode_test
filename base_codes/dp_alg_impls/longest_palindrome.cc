#include<cstdio>
#include<vector>
#include<string>

#include "../dp_algs.h"

std::string dp::longestPalindrome_v2(std::string s) {
    if (s.length() <=1) return s;
    int n = s.length();
    bool dp[n][n];
    std::fill_n(dp[0], n * n, false);
    /*
    if s[i]  == s[j], dp[i][j] = dp[i+1][j-1];
    */
   int left= n-1;
   int right = n-1;
   for (int i=n-1; i>=0; i--) {
       dp[i][i] = true;
       for(int j=i + 1; j< n; j++) {
         if (s[i] == s[j] && (j -i < 3||dp[i+1][j-1])) { // j-i<3 for aba type
             dp[i][j] = true;
             if (right - left < j - i) {
                 right = j;
                 left = i;
             }
         }
       }
   }

   return s.substr(left, right - left +1);
}

std::string dp::longestPalindrome_v3(std::string s) {
    if (s.length()<2) return s;
    int n = s.length();
    std::string result="";
    result += s[0];
    int max_len = 1;
    int left,right;
    for (int i=0; i<n-1; i++) {
        // aba format
        left = i;
        right = i;
        while(left >=0 && right <n && s[left] == s[right]) {
            left--;
            right++;
        }
        if (max_len < right - left -1) {
            max_len = right - left -1;
            result = s.substr(left+1, max_len);
        }
        // aa format
        if (s[i]==s[i+1]){
            left = i;
            right = i+1;
            while(left >=0 && right <n && s[left] == s[right]) {
                left--;
                right++;
            }
            if (max_len < right - left -1) {
                max_len = right - left -1;
                result = s.substr(left+1, max_len);
            }
        }
    }
    return result;
}

std::string dp::longestPalindrome_v4(std::string s) {
    int len = s.length();
    if (len <=1) return s;
    bool dp[len][len];
    std::fill_n(dp[0], len * len, false);
    // cover 只有单字符的情况
    int left = 0;
    int right = 0;
    int result = 1;
    for (int i=len-1; i>=0; i--) {
        dp[i][i] = true;
        for (int j=i+1; j<len; j++) {
            if (s[i]==s[j] && (j-i<2 || dp[i+1][j-1])) {
                dp[i][j] = true;
                if (result < j-i+1) {
                    result = j - i +1;
                    left = i;
                    right = j;
                }
            }
        }
    }
    return s.substr(left, right-left+1);
}