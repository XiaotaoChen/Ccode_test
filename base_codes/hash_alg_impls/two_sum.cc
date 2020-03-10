#include<vector>
#include <unordered_map>

#include "../hash_algs.h"

std::vector<int> hash_alg::twoSum(std::vector<int>& nums, int target) {
    std::vector<int>  result;
    if (nums.size()<2) return result;

    std::unordered_map<int, std::vector<int>> map;
    for (int i=0; i<nums.size(); i++) {
        if (map.find(nums[i])!=map.end()) {
            map[nums[i]].push_back(i);
        }
        else {
            map[nums[i]] = std::vector<int>(1, i);
        }
    }
    for (int i=0; i<nums.size(); i++) {
        if (nums[i] == target - nums[i]) {
            if (map[nums[i]].size()==2) {
                result = map[nums[i]];
                return result;
            }
        }
        else if (map.find(target- nums[i])!=map.end()) {
            result.push_back(i);
            result.push_back(map[target-nums[i]][0]);
            return result;
        }
    }
    return result;
}