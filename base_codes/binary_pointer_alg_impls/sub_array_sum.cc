#include <vector>
#include <unordered_map>
#include "../binary_pointer.h"

namespace binary_pointer
{

// int subarraySum(std::vector<int>& nums, int k) {
//     // std::vector<std::vector<int>> result;
//     int count = 0;
//     int target = k;

//     int left=0;
//     for (int i=0; i<nums.size(); i++) {
//         k -= nums[i];
//         if (k>0) continue;
//         else {
//             while(k<=0 && left <=i) {
//                 if (k==0) {
//                     // result.push_back(std::vector<int>(nums.begin()+left, nums.begin()+i));
//                     count++;
//                 }
//                 k += nums[left];
//                 left++;
//             }
//         }
//     }
//     while(left<nums.size()-1) {
//         k+=nums[left++];
//         if (k==0) {
//             count++;
//         }
//     }
//     return count;
// }

int subarraySum(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> map;
    map[0] = 1;
    int sum = 0;
    int cnt = 0;
    for (int i=0; i<nums.size(); i++) {
        sum += nums[i];
        if (map.find(sum-k)!=map.end()) {
            cnt += map[sum-k];
        }
        map[sum]++;
    }
    return cnt;
}

} // namespace binary_pointer
