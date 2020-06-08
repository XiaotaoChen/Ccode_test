#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>

#include "../sorts.h"

namespace sort
{

int maximumGap(std::vector<int>& nums) {
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

int maximumGap_v2(std::vector<int>& nums) {
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

int maximumGap_repeated(std::vector<int>& nums) {
    if (nums.size() < 2) return 0;
    int min = INT32_MAX;
    int max = INT32_MIN;
    
    for (int i=0; i<nums.size(); i++) {
        min = min < nums[i] ? min : nums[i];
        max = max > nums[i] ? max : nums[i];
    }

    // 桶间距 = 区间长度 / (ｎ个数字划分出的区间个数)
    int gap = (max -min) / (nums.size()-1);
    int bucket_num = (max - min) / gap + 1; 
    // 加１解决最大值的区间问题．　如nums=[2,4,6,8], gap=2, 不加１，　bucket_num=3, bucket_nums的下标=[0,1,2], 
    // 则最大值8映射bucket id时等于(8-2)/bucket_num=3, 不在bucket nums下标中，故多加一个bucket即可．其其实是解决开闭区间的问题：［2, 4), ［4, 6), ［6, 8)
    int buckets[bucket_num][2];
    for (int i=0; i<bucket_num; i++) {
        buckets[i][0] = INT32_MAX;
        buckets[i][1] = INT32_MIN;
    }

    for (int i=0; i < nums.size(); i++) {
        int idx = nums[i]/gap; // 除的是区间长度，而不是桶个数
        buckets[idx][0] = buckets[idx][0] < nums[i] ? buckets[idx][0] : nums[i];
        buckets[idx][1] = buckets[idx][1] > nums[1] ? buckets[idx][1] : nums[i];
    }

    // cal max gap
    int pre = -1;
    for (int i=0; i<bucket_num; i++) {
        if (buckets[i]!=0) {
            pre = i;
            break;
        }
    }

    int max_gap = 0;
    for (int i=pre+1; i < bucket_num; i++) {
        if (buckets[i][0]==INT32_MAX) continue;
        int gap = buckets[i][0] - buckets[pre][1];
        max_gap = max_gap > gap ? max_gap : gap;
        pre = i;
    }

    return max_gap;
}

int maximumGap_v2_repeated(std::vector<int>& nums) {
    if (nums.size() < 2) return 0;
    std::map<int, int, std::less<int>> mp;
    for (int i=0; i<nums.size(); i++) {
        mp[nums[i]]++;
    }

    int max_gap = 0;
    auto pre = mp.begin();
    for (auto iter=++mp.begin(); iter !=mp.end(); iter++) {
        int gap = iter->first - pre->first;
        max_gap = max_gap > gap ? max_gap : gap;
        pre = iter;
    }
    return max_gap;
}

} // namespace sort
