#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int count_reverse_pair_dfs(std::vector<int>& arr, int low, int high) {
    if (low == high) return 0;
    int mid = (low+high) / 2;
    int left = count_reverse_pair_dfs(arr, low, mid);
    int right = count_reverse_pair_dfs(arr, mid+1, high);

    int merge = 0;
    int tmp[high-low+1];
    int left_idx = mid;
    int right_idx = high;
    int tmp_idx = high-low;
    while(left_idx >=low && right_idx >mid) {
        if (arr[left_idx] > arr[right_idx]) {
            merge += right_idx - mid;
            tmp[tmp_idx--] = arr[left_idx--];

        }
        else {
            tmp[tmp_idx--] = arr[right_idx--];
        }
    }
    while(left_idx>=low) {
        tmp[tmp_idx--] = arr[left_idx--];
    }
    while(right_idx>mid) {
        tmp[tmp_idx--] = arr[right_idx--];
    }
    for (int i=low; i<=high; i++) arr[i] = tmp[i-low];
    
    return left + right + merge;
}

int count_reverse_pair(std::vector<int>& arr) {
    if (arr.size() <2) return 0;
    return count_reverse_pair_dfs(arr, 0, arr.size()-1);
}

} // namespace sword_finger_offer
