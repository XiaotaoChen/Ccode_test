#include <vector>

#include "../dp_algs.h"


int dp::maxSubArray(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n==1) return nums[0];

    int sum = 0;
    int max = INT32_MIN;
    for (int i=0; i<n;i++) {
        if (sum > 0) {
            sum += nums[i];
        }
        else {
            sum = nums[i];
        }
        max = max > sum ? max:sum;
    }
    return max;
}