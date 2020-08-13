#include <vector>
#include <iostream>
#include "../thot_50.h"

namespace thot_50 {

//O(k*N^2)
int superEggDrop(int K, int N) {
    if (K==0) return -1;
    if (N==0) return 0;
    int dp[K+1][N+1];
    std::fill_n(dp[0], (K+1) * (N+1), INT32_MAX);
    // col 0
    for (int i=0; i<=K; i++) {
        dp[i][0] = 0;
    }
    for (int i=1; i<=K; i++) {
        for (int j=1; j<=N; j++) {
            for (int k=1; k<=j;k++) {
                int val = std::max(dp[i-1][k-1], dp[i][j-k]);
                val = val < INT32_MAX? val+1:INT32_MAX;
                dp[i][j] = std::min(dp[i][j], val);
            }
        }
    }
    return dp[K][N];
}

// O(K*N*log(N))
int superEggDrop_v2(int K, int N) {
    if (K==0) return -1;
    if (N==0) return 0;
    int dp[K+1][N+1];
    std::fill_n(dp[0], (K+1) * (N+1), INT32_MAX);
    // col 0
    for (int i=0; i<=K; i++) {
        dp[i][0] = 0;
    }
    for (int i=1; i<=K; i++) {
        dp[i][1] = 1;
        for (int j=2; j<=N; j++) {
            int left = 1;
            int right = j;
            while(left +1 < right) {
                int mid = (left + right) / 2;
                int t1 = dp[i-1][mid-1];
                int t2 = dp[i][j-mid];
                if (t1 < t2) {
                    left = mid;
                }
                else if (t1 > t2) {
                    right = mid;
                }
                else {
                    left = right = mid;
                }
            }
            int val = std::min(std::max(dp[i-1][left-1], dp[i][j-left]), std::max(dp[i-1][right-1], dp[i][j-right]));
            dp[i][j] = val < INT32_MAX ? val+1:INT32_MAX;
        }
    }
    return dp[K][N];
}



// O(K*N)
int superEggDrop_v3(int K, int N) {
    if (K==0) return -1;
    if (N==0) return 0;
    int dp[K+1][N+1];
    std::fill_n(dp[0], (K+1) * (N+1), 0);
    int m =0;
    while(dp[K][m] < N) {
        m++;
        for (int k=1; k<=K; k++) {
            dp[k][m] = dp[k][m-1] + dp[k-1][m-1] + 1;
        }
    }
    return m;
}


}