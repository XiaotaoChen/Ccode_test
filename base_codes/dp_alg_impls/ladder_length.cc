#include<vector>
#include<climits> // INT_MAX
#include "../dp_algs.h"

bool dp::is_one_diff(const std::string& str1, const std::string& str2) {
    int len = str1.length();
    int diff = 0;
    for(int i=0; i<len; i++) {
        if (str1[i] != str2[i]) diff++;
    }
    if (diff==1) return true;
    return false;
}

int dp::ladderLength(std::string start, std::string end, std::unordered_set<std::string> &dict) {
    std::vector<std::string> all_str;
    all_str.push_back(start);
    for (std::unordered_set<std::string>::iterator iter = dict.begin(); iter != dict.end(); iter++) {
        all_str.push_back(*iter);
    }
    all_str.push_back(end);
    
    std::vector<int> dp(all_str.size());
    std::fill_n(dp, dp.size(), INT_MAX);
    dp[0] = 0;
    for (int i=1; i<dp.size(); i++) {
        if (is_one_diff(all_str[0], all_str[i])) dp[i] = 1;
    }
    // TODO by dp
    // for (int i=1; i<dp.size(); i++) {
        
    //     for()
    // }
    return 0
}