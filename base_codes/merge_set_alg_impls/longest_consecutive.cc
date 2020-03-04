#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>

#include "../merge_set.h" 

int merge_set::longestConsecutive(std::vector<int>& nums) {
    if (nums.size()==0) return 0;
    std::unordered_set<int> set;
    for (int i=0; i<nums.size(); i++) set.insert(nums[i]);

    int result = 0;
    for (int i=0; i<nums.size(); i++) {
        int val = nums[i];
        if (set.find(val)==set.end()) continue;
        int curr = 1;
        while(set.find(val-1)!=set.end()){
            val--;
            curr++;
            set.erase(val);
        }
        val = nums[i];
        while(set.find(val+1)!=set.end()) {
            val++;
            curr++;
            set.erase(val);
        }
        result = std::max(result, curr);
    }
    return result;
}


int merge_set::find_root(std::unordered_map<int,int>& nums, int x) {
    return nums[x] == x? x: nums[x] = find_root(nums, nums[x]);
}

int merge_set::merge_two_set(std::unordered_map<int,int>& nums, int x, int y, std::unordered_map<int,int>& cnts) {
    int x_r = find_root(nums, x);
    int y_r = find_root(nums, y);
    if (x_r==y_r) return cnts[x_r];
    nums[y_r]=x_r;
    cnts[x_r] +=cnts[y_r];
    return cnts[x_r];
}

int merge_set::longestConsecutive_v2(std::vector<int>& nums) {
    if (nums.size()==0) return 0;

    std::unordered_map<int,int> map1, cnts;
    for (int i=0; i<nums.size(); i++) {
        map1[nums[i]] = nums[i];
        cnts[nums[i]] =1;
    }
    int result = 1;
    for (int i=0; i<nums.size(); i++) {
        if (map1.find(nums[i]+1)!=map1.end()) {
            result = std::max(result, merge_two_set(map1, nums[i], nums[i]+1, cnts));
        }
    }
    return result;
}