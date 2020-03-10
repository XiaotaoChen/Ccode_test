#include <vector>
#include <algorithm>

#include "../hash_algs.h"


std::vector<std::vector<int>> hash_alg::fourSum(std::vector<int>& nums, int target) {
    // sort nums
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;

    int n = nums.size();
    for (int i=0; i<n-3; i++) {
        while (i>0 && i<n-3 && nums[i]==nums[i-1]) i++;
        for (int j=i+1; j<n-2; j++) {
            while(j>i+1 && j<n-2 && nums[j]==nums[j-1]) j++;
            int thrid = j+1;
            int fouth = n-1;
            while(thrid < fouth) {
                while(thrid>j+1 && thrid < fouth && nums[thrid] == nums[thrid-1]) thrid++;
                if (thrid==fouth) break;
                int curr = nums[i]+nums[j]+nums[thrid]+nums[fouth];
                if ( curr == target) {
                    result.push_back({nums[i], nums[j], nums[thrid], nums[fouth]});
                    thrid++;
                    fouth--;
                }
                else if (curr < target) {
                    thrid++;
                }
                else {
                    fouth--;
                }
            }
        }
    }
    return result;
}