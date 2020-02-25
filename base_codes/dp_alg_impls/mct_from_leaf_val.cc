#include <cstdio>
#include <vector>

#include "../dp_algs.h"


int dp::mctFromLeafValues(std::vector<int>& arr){
    if (arr.size() == 0) return 0;
    if (arr.size() == 2) return arr[0] * arr[1];
    int n = arr.size();
    
    int aux[n][n];
    std::fill_n(aux[0], n*n, -1);
    for (int i=0; i<n; i++) {
        aux[i][i]=arr[i];
        for (int j=i+1; j<n; j++) {
            aux[i][j] = aux[i][j-1] > arr[j] ? aux[i][j-1]:arr[j];
        }
    }
    
    int dp[n][n];
    std::fill_n(dp[0], n*n, 0);


    for (int d=1; d<n; d++) {
        for(int i=0; i<n; i++) {
            int j = i + d;
            if (j>=n) continue;
            int tmp = INT32_MAX;
            for (int k=i; k<j; k++) {
                tmp = std::min(tmp, aux[i][k] * aux[k+1][j] + dp[i][k] + dp[k+1][j]);
            }
            dp[i][j] = tmp;
        }
    }
    return dp[0][n-1];
}