#include "../dp_algs.h"

namespace dp
{

int numTrees(int n) {
    if (n==0) return 0;
    if (n==1) return 1;
    int arr[n][n];
    std::fill_n(arr[0], n*n, 0);
    for (int i=0; i<n; i++) arr[i][i] = 1;
    for (int i=n-2; i>=0; i--) {
        for (int j=i+1; j<n;j++) {
            arr[i][j] += arr[i+1][j]; // first i is head, only has right subtree
            for (int k=i+1; k<j; k++) {
                arr[i][j] += arr[i][k-1] * arr[k+1][j];
            }
            arr[i][j] += arr[i][j-1]; // last j is head, only has left substree;
        }
    }
    return arr[0][n-1];
}

} // namespace dp
