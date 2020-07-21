#include <vector>
#include "../hot_100.h"

namespace hot_100
{

bool canPartition_dfs(std::vector<int>& nums, int index, int target) {
    if (index==nums.size()) return false;
    if (target == nums[index]) return true;
    if (target > nums[index]) {
        bool flag = canPartition_dfs(nums, index+1, target - nums[index]);
        if (flag) return true;
    }
    return canPartition_dfs(nums, index+1, target);
}

bool canPartition(std::vector<int>& nums) {
    int sum = 0;
    for (int i=0; i<nums.size(); i++) sum += nums[i];
    if (sum==0 || sum%2==1) return false;
    return canPartition_dfs(nums, 0, sum/2);
}

bool canPartition_V2(std::vector<int>& nums) {
    int sum = 0;
    for (int i=0; i<nums.size(); i++) sum += nums[i];
    if (sum%2==1) return false;
    sum /= 2;
    int len = nums.size();
    bool dp[len+1][sum+1];
    std::fill_n(dp[0], (len+1)*(sum+1), false);
    for (int i=0; i<=len; i++) dp[i][0] = true;
    for (int i=1; i<=len; i++) {
        for (int j=1; j<=sum; j++){
            dp[i][j] = dp[i-1][j];
            if (nums[i-1] <= j) {
                dp[i][j] = dp[i][j] || dp[i-1][j - nums[i-1]];
            }
        }
    }
    return dp[len][sum];
}

bool canPartition_V3(std::vector<int>& nums) {
    int sum = 0;
    for (int i=0; i<nums.size(); i++) sum += nums[i];
    if (sum%2==1) return false;
    sum /= 2;
    int len = nums.size();
    bool dp[sum+1];
    std::fill_n(dp, sum+1, false);
    dp[0] = true;
    for (int i=1; i<=len; i++) {
        for (int j=sum; j>=0; j--){
            if (nums[i-1] <= j) {
                dp[j] = dp[j]|| dp[j - nums[i-1]];
            }
        }
    }
    return dp[sum];
}

} // namespace hot_100
