#include <string>
#include "../dp_algs.h"

namespace dp
{

bool is_match(char a, char b) {
    if (a == b|| b=='.') return true;
    return false;
}

bool regular_match_v3(std::string& s, std::string& p) {
    if (s.length()==0 && p.length()==0) return true;
    if (p.length()==0) return false;
    int n = s.length();
    int m = p.length();
    bool flags[n+1][m+1];
    std::fill_n(flags[0], (n+1)*(m+1), false);
    flags[0][0]=true;
    for (int i=1; i<m; i+=2) {
        if (p[i]=='*' && flags[0][i-1]) flags[0][i+1] = true;
        else break;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (p[j]=='*') {
                if (j==0) continue;
                // match 0 number
                if (j>=2 && flags[i+1][j-1]) {
                    flags[i+1][j+1] = true;
                    continue;
                }
                // match >=1
                int tmp_idx = i;
                while(tmp_idx>=0 && is_match(s[tmp_idx], p[j-1])) {
                    if (flags[tmp_idx+1][j]) {
                        flags[i+1][j+1] = true;
                        break;
                    }
                    tmp_idx--;
                }
            }
            else if (is_match(s[i], p[j]) && flags[i][j]) {
                flags[i+1][j+1] = true;
            }
        }
    }
    return flags[n][m];
}

} // namespace dp
