#ifndef HASH_ALG_
#define HASH_ALG_

#include <vector>

namespace hash_alg
{

// https://leetcode-cn.com/problems/two-sum/
std::vector<int> twoSum(std::vector<int>& nums, int target);

// https://leetcode-cn.com/problems/4sum/
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);


} // namespace hash


#endif