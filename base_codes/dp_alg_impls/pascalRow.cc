#include <cstdio>
#include <vector>

#include "../dp_algs.h"

std::vector<int> dp::getRow(int rowIndex) {
    std::vector<int> result;
    if (rowIndex==0) {
        result.push_back(1);
        return result;
    }
    else if (rowIndex==1) {
        result.push_back(1);
        result.push_back(1);
        return result;
    }
    int dp[2][rowIndex+1];
    std::fill_n(dp[0], (rowIndex+1) * 2, 1);
    for (int i=2;i<=rowIndex; i++) {
        for (int j=1; j<i;j++) {
            dp[i%2][j] = dp[(i-1)%2][j-1] + dp[(i-1)%2][j];
        }
    }
    int line = rowIndex%2;
    for (int i=0; i<=rowIndex; i++) result.push_back(dp[line][i]);
    return result;
}

std::vector<std::vector<int> > dp::generate(int numRows) {
    std::vector<std::vector<int> > result;
    if (numRows==0) return result;
    if (numRows==1) {
        std::vector<int> line1 {1};
        result.push_back(line1);
        return result;
    }
    if (numRows==2) {
        std::vector<int> line1 {1};
        std::vector<int> line2 {1,1};
        result.push_back(line1);
        result.push_back(line2);
        return result;
    }
    std::vector<int> line1 {1};
    std::vector<int> line2;
    line2.push_back(1);
    line2.push_back(1);
    result.push_back(line1);
    result.push_back(line2);

    int dp[2][numRows];
    std::fill_n(dp[0], numRows * 2, 1);
    for (int i=3;i<=numRows; i++) {
        for (int j=1; j<i-1;j++) {
            dp[i%2][j] = dp[(i-1)%2][j-1] + dp[(i-1)%2][j];
        }
        int index = i%2;
        std::vector<int> line;
        for (int j=0;j<i;j++) line.push_back(dp[index][j]);
        result.push_back(line);
    }
    return result;
}