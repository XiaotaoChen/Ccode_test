#include <vector>
#include <stack>
#include "../hot_100.h"

namespace hot_100
{

int lengthOfLIS(std::vector<int>& nums) {
    if (nums.size()<2) return nums.size();
    
    int result = 0;
    std::stack<int> st;
    for (int i=0; i<nums.size(); i++) {
        while(!st.empty() && st.top() >= nums[i]) st.pop();
        st.push(nums[i]);
        result = result > st.size() ? result : st.size();
    }
    return result;
}

int lengthOfLIS_V2(std::vector<int>& nums) {
    if (nums.size() <2) return nums.size();
    int n = nums.size();
    int dp[n];
    int result = 1;
    std::fill_n(dp, n, 1);
    for (int i=1; i<n; i++) {
        for (int j=i-1; j>=0; j--) {
            if (nums[j] < nums[i]) {
                dp[i] = dp[i] > dp[j]+1 ? dp[i]: dp[j] + 1;
            }
        }
        result = result > dp[i] ? result : dp[i];
    }
    return result;
}

} // namespace hot_100
