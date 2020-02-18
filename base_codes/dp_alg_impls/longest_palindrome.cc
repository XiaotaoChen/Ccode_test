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