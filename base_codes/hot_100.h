#ifndef HOT_100_IMPLS
#define HOT_100_IMPLS

#include <vector>
#include <string>
#include "./data_structs/base_struct.h"

namespace hot_100
{

// https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
int findKthLargest(std::vector<int>& nums, int k);
int findKthLargest_min_heap(std::vector<int>& nums, int k);

// https://leetcode-cn.com/problems/sliding-window-maximum/
std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k);
std::vector<int> maxSlidingWindow_v2(std::vector<int>& nums, int k);

// https://leetcode-cn.com/problems/search-a-2d-matrix-ii/
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target);

// https://leetcode-cn.com/problems/perfect-squares/
int numSquares(int n);

// https://leetcode-cn.com/problems/longest-increasing-subsequence/
int lengthOfLIS(std::vector<int>& nums);
int lengthOfLIS_V2(std::vector<int>& nums);

// https://leetcode-cn.com/problems/queue-reconstruction-by-height/
std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people);


// https://leetcode-cn.com/problems/path-sum-iii/
int pathSum(TreeNode* root, int sum);

// https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/
std::vector<int> findDisappearedNumbers(std::vector<int>& nums);

// https://leetcode-cn.com/problems/daily-temperatures/
std::vector<int> dailyTemperatures(std::vector<int>& T);

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
int maxProfit(std::vector<int>& prices);


// https://leetcode-cn.com/problems/burst-balloons/
int maxCoins(std::vector<int>& nums);

// https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/
int findUnsortedSubarray(std::vector<int>& nums);

// https://leetcode-cn.com/problems/house-robber-iii/
int rob(TreeNode* root);


// https://leetcode-cn.com/problems/counting-bits/
std::vector<int> countBits(int num);

// https://leetcode-cn.com/problems/decode-string/
std::string decodeString(std::string s);
std::string decodeString_V2(std::string s);

// https://leetcode-cn.com/problems/partition-equal-subset-sum/
bool canPartition(std::vector<int>& nums);
bool canPartition_V2(std::vector<int>& nums);
bool canPartition_V3(std::vector<int>& nums);


// https://leetcode-cn.com/problems/task-scheduler/
int leastInterval(std::vector<char>& tasks, int n);

// https://leetcode-cn.com/problems/palindromic-substrings/
int countSubstrings(std::string s);

} // namespace hot_100


#endif