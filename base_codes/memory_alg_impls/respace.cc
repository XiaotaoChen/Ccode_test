#include <vector>
#include <string>
#include <unordered_set>

#include "../memory_algs.h"

int memory_alg::respace(std::vector<std::string>& dictionary, std::string sentence) {
    int n = sentence.length();
    if (n==0) return 0;
    int dp[n+1];
    std::fill_n(dp, n+1, INT32_MAX);
    // std::vector<int> dp(n+1, INT32_MAX);
    dp[0] = 0;

    std::unordered_set<std::string> set;
    for (int i=0; i<dictionary.size(); i++) set.insert(dictionary[i]);

    for (int i=0; i<n; i++) {
        int tmp = INT32_MAX;
        for (int j=0; j<=i; j++) {
            if (set.find(sentence.substr(j, i-j+1))!=set.end()) {
                tmp = std::min(dp[j], tmp);
            }
        }
        dp[i+1] = std::min(tmp, dp[i]+1);
    }

    return dp[n];
}