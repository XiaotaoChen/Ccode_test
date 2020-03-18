#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>

#include "../sorts.h"

int sort::maximumGap(std::vector<int>& nums) {
    int n = nums.size();
    if (n<2) return 0;
    if (n==2) {
        int max = nums[0]>nums[1] ? nums[0]:nums[1];
        int min = nums[0]<nums[1] ? nums[0]:nums[1];
        return max-min;
    }
    int min = INT32_MAX;
    int max = INT32_MIN;
    std::unordered_set<int> set;
    for (int i=0; i<n;i++) {
        if (set.find(nums[i])!=set.end()) continue;
        set.insert(nums[i]);
        min = min<nums[i]? min: nums[i];
        max = max>nums[i]? max: nums[i];
    }
    if (set.size()==1) return 0;
    int bucketlength = (max - min)/(set.size()-1);
    int bucket_num = (max - min) /  bucketlength + 1;
    std::vector<std::pair<int, int>> buckets(bucket_num, {INT32_MAX,INT32_MIN});
    for (int i=0; i<n; i++) {
        int bucket_idx = (nums[i] - min) / bucketlength;
        buckets[bucket_idx].first = buckets[bucket_idx].first < nums[i]? buckets[bucket_idx].first : nums[i];
        buckets[bucket_idx].second = buckets[bucket_idx].second > nums[i]? buckets[bucket_idx].second : nums[i];
    }

    int maxgap = 0;
    int pre = -1;
    for (int i=0; i<buckets.size(); i++) {
        if (buckets[i].first!=INT32_MAX) {
            pre = i;
            break;
        }
    }

    for (int i=pre+1; i<buckets.size(); i++) {
        if (buckets[i].first == INT32_MAX) continue;
        int tmp = buckets[i].first - buckets[pre].second;
        maxgap = maxgap > tmp ? maxgap : tmp;
        pre = i;
    }
    return maxgap;
}

int sort::maximumGap_v2(std::vector<int>& nums) {
    int n = nums.size();
    if (n<2) return 0;
    std::map<int, int , std::less<int>> mp;
    for (int i=0; i<n; i++) {
        mp[nums[i]]++;
    }
    if (mp.size()==1) return 0;
    int maxgap = 0;
    int pre = (*mp.begin()).first;
    for (std::map<int ,int>::iterator iter = ++mp.begin(); iter!=mp.end(); iter++) {
        int curr = (*iter).first - pre;
        maxgap = maxgap > curr? maxgap: curr;
        pre = (*iter).first;
    }
    return maxgap;
}