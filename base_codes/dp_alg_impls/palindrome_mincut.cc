#include <vector>
#include <string>
#include "../dp_algs.h"

namespace dp
{

int palindrome_minCut(std::string& str) {
    if (str.length()==0) return 0;
    if (str.length()==1) return 1;
    int n = str.length();
    int dps[n][n];
    for (int i=0; i<n; i++) dps[i][i] = 1;
    for (int i=n-2; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            if (str[i]==str[j]) {
                if (j-i<2) dps[i][j] = 1;
                else dps[i][j] = dps[i+1][j-1] + 1;
            }
            else {
                dps[i][j] = INT32_MAX;
                for (int k=i; k<j; k++) {
                    dps[i][j] = dps[i][j] < dps[i][k] + dps[k+1][j] ? dps[i][j] : dps[i][k] + dps[k+1][j];
                }
            }
        }
    }
    return dps[0][n-1];
}

} // namespace dp
