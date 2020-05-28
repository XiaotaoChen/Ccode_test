#include <vector>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int get_first_index(std::vector<int>& arr, int left, int right, int num) {
    if (left>right) return -1;
    // if (left==right) return left;
    int mid = (left+right) / 2;
    if (arr[mid]==num) {
        if (mid == 0 || arr[mid-1] < num) return mid;
        return get_first_index(arr, left, mid-1, num);
    }
    if (arr[mid]> num) return get_first_index(arr, left, mid-1, num);
    return get_first_index(arr, mid+1, right, num);
}

int get_last_index(std::vector<int>& arr, int left, int right, int num) {
    if (left > right) return -1;
    // if (left == right) return left;
    int mid = (left+right) / 2;
    if (arr[mid] == num) {
        if (arr[mid]==num) {
            if (mid==arr.size()-1 || arr[mid+1]>num) return mid;
            return get_last_index(arr, mid+1, right, num);
        }
    }
    if (arr[mid]>num) return get_last_index(arr, left, mid-1, num);
    return get_last_index(arr, mid+1, right, num);
}

int sorted_arr_count(std::vector<int>& arr, int num) {
    if (arr.size()==0) return 0;
    int left_idx = get_first_index(arr, 0, arr.size()-1, num);
    int result = 0;
    if (left_idx!=-1) {
        int right_idx = get_last_index(arr, 0, arr.size()-1, num);
        result = right_idx - left_idx +1;
    }
    return result;
}

int get_index(std::vector<int>& arr, int left, int right, int num) {
    if (left > right) return -1;
    // if (left == right) return left;
    int mid = (left+right) / 2;
    if (arr[mid] == num) {
        return mid;
    }
    if (arr[mid]>num) return get_index(arr, left, mid-1, num);
    return get_index(arr, mid+1, right, num);
}

int sorted_arr_count_v2(std::vector<int>& arr, int num) {
    if (arr.size() == 0) return 0;
    int index = get_index(arr, 0, arr.size()-1, num);
    if (index ==  -1) return 0;
    int left = index;
    int right = index;
    while(left-1>=0 && arr[left-1]==arr[index]) left--;
    while(right <arr.size() && arr[right+1]==arr[index]) right++;
    return right-left +1;
}

} // namespace sword_finger_offer
