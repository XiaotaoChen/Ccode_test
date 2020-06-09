#include <vector>
#include <map>
#include <algorithm>
#include <set>

namespace sort
{

bool compare(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;
}

std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::vector<int> result;
    if (nums.size()==0 || nums.size() < k) return result;
    if (nums.size()==1 && k==1) {
        result.push_back(nums[0]);
        return result;
    }

    std::map<int, int> mp;
    for (int i=0; i<nums.size(); i++) {
        mp[nums[i]]++;
    }

    std::vector<std::pair<int, int>> tmp;
    for (auto& p: mp) {
        tmp.push_back(std::make_pair(p.first, p.second));
    }

    std::sort(tmp.begin(), tmp.end(), compare);


    for (int i=0; i<k; i++) {
        result.push_back(tmp[i].first);
    }
    return result;

}

std::vector<int> topKFrequent_v2(std::vector<int>& nums, int k) {
    std::vector<int> result;
    if (nums.size()==0 || nums.size() < k) return result;
    if (nums.size()==1 && k==1) {
        result.push_back(nums[0]);
        return result;
    }

    std::map<int, int> mp;
    for (int i=0; i<nums.size(); i++) {
        mp[nums[i]]++;
    }

    std::multiset<std::pair<int, int>, std::less<std::pair<int, int>>> st;
    for (auto& p: mp) {
        if (st.size() < k) {
            st.insert(std::make_pair(p.second, p.first));
        }
        else {
            if ((*st.begin()).first < p.second) {
                st.erase(st.begin());
                st.insert(std::make_pair(p.second, p.first));
            }
        }
    }
    
    for (auto & t: st) {
        result.push_back(t.second);
    }
    return result;

}

} // namespace sort
