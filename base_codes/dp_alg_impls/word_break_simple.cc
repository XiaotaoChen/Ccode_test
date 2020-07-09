#include <string>
#include <vector>
#include <unordered_set>
#include "../dp_algs.h"

namespace dp
{

bool wordBreak_single(std::string s, std::vector<std::string>& wordDict) {
    if (s.length()==0) return true;
    if (wordDict.size()==0) return false;
    int len = s.length();
    std::unordered_set<std::string> us;
    for (int i=0; i<wordDict.size(); i++) us.insert(wordDict[i]);
    bool flags[len];
    std::fill_n(flags, len, false);
    for (int i=0; i<len; i++) {
        for (int j=0; j<=i; j++) {
            if ((j==0||flags[j-1]) && us.find(s.substr(j, i-j+1))!=us.end()) {
                flags[i] = true;
            }
        }
    }
    return flags[len-1];
}

} // namespace dp
