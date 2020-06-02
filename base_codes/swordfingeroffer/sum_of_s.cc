#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::pair<int, int> sum_of_s(std::vector<int>& arr, int s) {
    if (arr.size()<2) return std::make_pair(-1,-1);
    int left = 0;
    int right = arr.size() - 1;
    while(left<right) {
        int tmp = arr[left] + arr[right];
        if ( tmp == s){
            break;
        }
        else if (tmp > s) {
            right--;
        }
        else {
            left++;
        }
    }
    if (left==right) return std::make_pair(-1,-1);
    return std::make_pair(arr[left], arr[right]);
}

std::vector<std::vector<int>> sum_of_s_v2(int num) {
    std::vector<std::vector<int>> result;
    if (num<=2) return result;
    int small = 1;
    int big = 2;
    int target_small = num / 2;
    while(small <= target_small) {
        int sum = int((small+big)*(big-small+1)/2);
        if ( sum == num) {
            std::vector<int> tmp;
            for (int i=small; i<=big; i++) tmp.push_back(i);
            result.push_back(tmp);
            small++;
        }
        else if (sum < num) {
            big++;
        }
        else {
            small++;
        }
    }
    return result;
}

} // namespace sword_finger_offer
