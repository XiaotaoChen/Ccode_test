#include <vector>
#include <numeric> // accumulate
#include <unordered_map>
#include <iostream>
#include <math.h> // pow

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void probability_dfs(int combinations[], int & curr, int depth) {
    if (depth==0) {
        combinations[curr]++;
        // for (int i=0; i<=curr; i++) {
        //     std::cout << combinations[i] << " ";
        // }
        // std::cout << std::endl;
        return;
    }
    depth--;
    for (int i=1; i<=6; i++) {
        curr += i;
        probability_dfs(combinations, curr, depth);
        curr -= i;
    }
}

std::unordered_map<int, float> probability_n(int n) {
    std::unordered_map<int, float> mp;
    if (n==0) return mp;

    int counts[6*n+1];
    std::fill_n(counts, 6*n+1, 0);
    int curr=0;
    probability_dfs(counts, curr, n);
    // int sum = std::accumulate(counts+n, counts+6*n+1, 0);
    int sum = pow(6, n);
    std::cout << "sum: " << sum << std::endl;

    for (int i=n; i<=6*n; i++) {
        mp[i] = 1.0 * counts[i]/sum;
    }
    return mp;

}

} // namespace sword_finger_offer
