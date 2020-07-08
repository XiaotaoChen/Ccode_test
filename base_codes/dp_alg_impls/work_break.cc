#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include "../dp_algs.h"

namespace dp
{

std::vector<std::string> wordBreak(std::string s, std::unordered_set<std::string> &dict) {
    std::vector<std::string> result;
    if (s.length()==0 || dict.size()==0) return result;
    int len = s.length();
    std::vector<std::vector<int>> traces(len, std::vector<int>());
    bool flags[len];
    std::fill_n(flags, len, false);
    for (int i=0; i<len; i++) {
        for (int j=0; j<=i;j++) {
            if ((j==0 || flags[j-1]) && dict.find(s.substr(j, i-j+1))!=dict.end()) {
                flags[i] = true;
                traces[i].push_back(j-1);
            }
        }
    }

    // for (int i=0; i<len;i++) {
    //     if (flags[i]) {
    //         std::cout << i << " is true: ";
    //         for (int j=0; j<traces[i].size(); j++) std::cout << traces[i][j] << " ";
    //         std::cout << std::endl;
    //     }
    // }


    std::vector<std::vector<std::string>> paths(len, std::vector<std::string>());

    for (int i=1; i<len; i++) {
        if (!flags[i]) continue;
        for (int j=0; j<traces[i].size(); j++) {
            int pre_idx = traces[i][j];
            if (pre_idx==-1) {
                paths[i].push_back(s.substr(0, i+1));
            }
            else{
                for (int k=0; k<paths[pre_idx].size(); k++) {
                    std::string tmp = paths[pre_idx][k] + " " + s.substr(pre_idx+1, i-pre_idx);
                    paths[i].push_back(tmp);
                }
            }
        }
    }
    return paths[len-1];
}

} // namespace dp
