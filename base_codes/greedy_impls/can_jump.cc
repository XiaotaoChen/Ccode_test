#include <vector>
#include <algorithm>

#include "../greedy_algs.h"

bool greedy::canJump(std::vector<int>& nums) {
    if (nums.size() == 0) return true;
    int k = 0;
    for(int i=0; i<nums.size(); i++){
        if (k<i) return false;
        k = std::max(k, nums[i] +i);
    }
    return true;
}

int greedy::jump(std::vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int n = nums.size();
    int results[n];
    std::fill_n(results, n , 0);

    int k = 0;
    for (int i=0;i<n; i++) {
        if (k<i) break;
        k = std::max(k, nums[i] + i);
        for (int j=nums[i]; j>0; j--) {
            if (i + j >= n) continue;
            if (results[i+j] != 0) break;
            results[i+j] = results[i] + 1;
        }
    }
    return results[n-1];
}
