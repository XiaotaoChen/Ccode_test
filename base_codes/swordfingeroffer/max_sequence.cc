#include <vector>
#include <deque>
#include <set>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::vector<int> max_sequence(std::vector<int>& arr, int windows) {
    std::vector<int> result;
    if (arr.size() < windows) return result;
    std::deque<int> curr_max_idxs;
    for (int i=0; i<windows-1; i++) {
        if (curr_max_idxs.size()>0 && arr[*curr_max_idxs.rbegin()] <= arr[i]) curr_max_idxs.pop_back();
        curr_max_idxs.push_back(i);
    }

    for (int i=windows-1; i<arr.size(); i++) {
        if (curr_max_idxs.size()>0 && arr[*curr_max_idxs.rbegin()] <= arr[i]) curr_max_idxs.pop_back();
        if (curr_max_idxs.size()>0 && (i-(*curr_max_idxs.begin())) >= windows) curr_max_idxs.pop_front();
        curr_max_idxs.push_back(i);
        result.push_back(arr[curr_max_idxs.front()]);
    }
    return result;
}

std::vector<int> max_sequence_v2(std::vector<int>& arr, int windows) {
    std::vector<int> result;
    if (arr.size() < windows) return result;
    std::multiset<int> st;
    for (int i=0; i<windows-1; i++) st.insert(arr[i]);
    for (int i=windows-1;i<arr.size(); i++) {
        st.insert(arr[i]);
        result.push_back(*st.rbegin());
        st.erase(arr[i-2]);
    }
    return result;
}

} // namespace sword_finger_offer
