#include "../dfs_algs.h"

namespace dfs
{

int numTrees_dfs(int left, int right) {
    if (left >= right) return 1;
    int count = 0;
    for (int i=left; i<=right; i++) {
        count += numTrees_dfs(left,i-1) * numTrees_dfs(i+1, right);
    }
    return count;
}

int numTrees(int n) {
    return numTrees_dfs(0, n-1);
}

} // namespace dfs
