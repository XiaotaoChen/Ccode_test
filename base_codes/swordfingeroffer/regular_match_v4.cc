#include <vector>
#include "../dp_algs.h"

namespace dp
{

bool is_match_v4(char a, char b) {
    return a==b || b == '.';
}

bool regular_match_v4(std::string& s, std::string& p) {
    int n = s.length();
    int m = p.length();
    if (n>0 && m ==0) return false;
    int flags[n+1][m+1];
    std::fill_n(flags[0], (n+1)*(m+1), false);
    flags[0][0] = true;
    for (int i=2; i<=m; i+=2) {
        if (p[i-1]=='*') flags[0][i] = flags[0][i-2];
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (p[j-1] != '*') {
                if (is_match_v4(s[i-1], p[j-1])) flags[i][j] = flags[i-1][j-1];
            }
            else {
                // match 0
                flags[i][j] = flags[i][j-2];
                if (flags[i][j]) continue;
                //match one or more
                int idx = i;
                while(idx>0 && is_match_v4(s[idx-1], p[j-2])) {
                    if (flags[idx][j-1]) {
                        flags[i][j] = true;
                        break;
                    }
                    idx--;
                }
            }
        }
    }
    return flags[n][m];
}

} // namespace dp
