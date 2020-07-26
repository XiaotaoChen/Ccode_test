#include <string>
#include "../algorithm.h"

namespace hot_100
{

int countSubstrings(std::string s) {
    int len = s.length();
    if (len <= 1) return len;
    bool dp[len][len];
    std::fill_n(dp[0], len*len, 0);
    for (int i=0; i<len; i++) dp[i][i] = true;
    int result = len;
    for (int i=len-2; i>=0; i--) {
        for (int j=i+1; j<len; j++) {
            if ((j-i<2|| dp[i+1][j-1]) && s[i]==s[j]) {
                dp[i][j] = true;
                result++;
            }
        }
    }
    return result;
}

} // namespace hot_100
