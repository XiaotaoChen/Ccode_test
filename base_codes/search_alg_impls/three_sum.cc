#include <cstdio>
#include <vector>
#include <algorithm> // sort

#include "../search_algs.h"

std::vector<std::vector<int>> search::threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    if (nums.size() <3) return result;
    std::sort(nums.begin(), nums.end());

    int len = nums.size();
    for (int i=0;i<len; i++) {
        if (i>0 && nums[i]==nums[i-1]) continue;
        int L = i+1;
        int R = len -1;
        while(L<R) {
            if (nums[L] + nums[R] == -nums[i]) {
                result.push_back({nums[i], nums[L], nums[R]});
                while(L<R && nums[L] == nums[L+1]) L++;
                while(L<R && nums[R] == nums[R-1]) R--;
                L++;
                R--;
            }
            else if (nums[L] + nums[R] < -nums[i]) L++;
            else R--;
        }
    }
    return result;
}