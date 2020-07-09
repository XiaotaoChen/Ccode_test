#include <vector>
#include <string>
#include "../dp_algs.h"

namespace dp
{

std::string longestPalindrome_v5(std::string s) {
    if (s.length()<2) return s;
    int n = s.length();
    bool flags[n][n];
    std::fill_n(flags[0], n*n, false);
    for (int i=0; i<n; i++) flags[i][i] = true;

    int max_len = 1;
    int idx = 0;
    for (int i=n-2; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            if (s[i]==s[j] && (j-i<2 || flags[i+1][j-1])) {
                flags[i][j] = true;
                if (j-i+1 > max_len) {
                    max_len = j-i+1;
                    idx = i;
                }
            }
        }
    }
    return s.substr(idx, max_len);
}

} // namespace dp
