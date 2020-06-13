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

std::vector<std::vector<int>> search::threeSum_v2(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    if (nums.size()<3) return result;
    std::sort(nums.begin(), nums.end(),std::less<int>());

    int len = nums.size();
    for (int i=0; i<len-2; i++) {
        if (i>0 && nums[i]== nums[i-1]) continue;
        if (nums[i] > 0) break;
        for (int j=i+1; j< len-1; j++) {
            if (j > i+1 && nums[j]==nums[j-1]) continue;
            if (nums[i] + nums[j] >0) break;
            for (int k=j+1;k<len; k++) {
                if (k > j+1 && nums[k]==nums[k-1]) continue;
                if (nums[i]+nums[j] == -nums[k]) {
                    result.push_back({nums[i], nums[j], nums[k]});
                    break;
                }
                if (nums[i] + nums[j] >= -nums[k]) break;
            }
        }
    }
    return result;

}

std::vector<std::vector<int>> search::threeSum_v3(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    if (nums.size()<3) return result;
    std::sort(nums.begin(), nums.end(),std::less<int>());

    int len = nums.size();
    for (int i=0; i<len-2; i++) {
        if (i>0 && nums[i] == nums[i-1]) continue;
        if (nums[i]>0) break;
        int left = i+1;
        int right = len-1;
        while(left < right) {
            if (nums[left]+nums[right] == -nums[i]) {
                result.push_back({nums[i], nums[left], nums[right]});
                while(left < right && nums[left] == nums[left+1]) left++;
                while(left < right && nums[right] == nums[right-1]) right--;
                left++;
                right--;
            }
            else if (nums[left] + nums[right] < -nums[i]) left++;
            else right--;
        }
    }
    return result;
}