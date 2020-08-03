#include <vector>
#include <deque>
#include <set>
#include <stddef.h>
#include "../hot_100.h"

namespace hot_100
{

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> result;
    if (nums.size() < k) return result;
    std::deque<int> qidx;
    for (int i=0; i<k-1;i++) {
        while(!qidx.empty() && nums[i] >= nums[qidx.back()]) qidx.pop_back();
        qidx.push_back(i);
    }

    for (int i=k-1; i<nums.size(); i++) {
        if (!qidx.empty() && i - qidx.front() >k-1 ) qidx.pop_front();
        while(!qidx.empty() && nums[i] >= nums[qidx.back()]) qidx.pop_back();
        qidx.push_back(i);
        result.push_back(nums[qidx.front()]);
    }
    return result;
}

std::vector<int> maxSlidingWindow_v2(std::vector<int>& nums, int k) {
    std::vector<int> result;
    if (nums.size() < k) return result;
    std::multiset<int, std::greater<int> > st;
    for (int i=0; i<k-1; i++) st.insert(nums[i]);
    for (int i=k-1; i<nums.size(); i++) {
        st.insert(nums[i]);
        result.push_back(*st.begin());
        st.erase(nums[i-k+1]);
    }
    return result;
}

} // namespace hot_100
