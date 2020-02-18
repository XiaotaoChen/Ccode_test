#include<cstdio>
#include<vector>
#include<string>

#include "../search_algs.h"

std::string search::z_convert(std::string s, int numRows) {
    if (numRows==1) return s;
    std::vector<std::vector<char>> row_chs(numRows);
    int Round = 2 * numRows - 2;
    for(int i=0; i< s.length(); i++) {
        int idx = i % Round;
        if (idx < numRows) row_chs[idx].push_back(s[i]);
        else {
            idx = Round - idx;
            row_chs[idx].push_back(s[i]);
        }
    }

    std::string result = "";
    for(int i=0; i< numRows; i++) {
        for(int j=0; j<row_chs[i].size(); j++) {
            result += row_chs[i][j];
        }
    }
    return result;
}