#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../merge_set.h"


namespace merge_set
{

int longestConsecutive_V3(std::vector<int>& nums) {
    if (nums.size() <2) return nums.size();
    std::unordered_set<int> st;
    for (int i=0; i<nums.size(); i++) {
        if (st.find(nums[i])==st.end()) {
            st.insert(nums[i]);
        }
    }
    int result = 0;
    while(st.size()>0) {
        int num = *st.begin();
        int tmp = num;
        int curr = 0;
        while(st.find(tmp)!=st.end()) {
            curr++;
            st.erase(tmp);
            tmp--;
        }
        tmp = num+1;
        while(st.find(tmp)!=st.end()) {
            curr++;
            st.erase(tmp);
            tmp++;
        }
        result = result > curr ? result:curr;
    }
    return result;
}

int find_root_V4(std::unordered_map<int, int>& mp, int x) {
    return mp[x] == x ? x: mp[x] = find_root_V4(mp, mp[x]);
}

int merge_set_V4(std::unordered_map<int, int>& mp, int x, int y, std::unordered_map<int, int>& cnts) {
    int x_r = find_root_V4(mp, x);
    int y_r = find_root_V4(mp, y);
    if (x_r == y_r) return cnts[x_r];
    mp[y_r] = x_r;
    cnts[x_r] += cnts[y_r];
    return cnts[x_r];
}


int longestConsecutive_V4(std::vector<int>& nums) {
    if (nums.size() < 2) return nums.size();
    
    // 假设输入无重复数据
    std::unordered_map<int, int> mp, cnts;
    for (int i=0; i<nums.size(); i++) {
        mp[nums[i]] = nums[i];
        cnts[nums[i]]=1;
    }

    int result = 0;
    for (int i=0; i<nums.size(); i++) {
        int cnt = 0;
        if (mp.find(nums[i]+1) != mp.end()) {
            cnt = merge_set_V4(mp, nums[i], nums[i]+1, cnts);
        }
        else {
            cnt = cnts[nums[i]];
        }
        result = result > cnt ? result : cnt;
    }
    return result;
}

} // namespace merge_set
