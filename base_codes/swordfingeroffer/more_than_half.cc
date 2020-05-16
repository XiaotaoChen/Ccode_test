#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int partition(std::vector<int>& arr, int begin, int end) {
    if (begin == end) return begin;
    int small = begin -1;
    for (int i=begin; i<end; i++) {
        if (arr[i] >= arr[end]) continue;
        small++;
        if (small != i) swap<int>(arr[small], arr[i]);
    }
    small++;
    swap<int>(arr[small], arr[end]);
    return small;
}

int MoreThanHalf(std::vector<int>& arr) {
    if (arr.size()==0) return -1;
    int mid = arr.size() / 2;
    int begin = 0;
    int end = arr.size() -1;
    
    while(begin <end) {
        int idx = partition(arr, begin, end);
        if (idx==mid) break;
        if (idx>mid) {
            end = idx-1;
        }
        else {
            begin = idx+1;
        }
    }
    // check number is more than half
    int number = arr[mid];
    int times = 0;
    for (int i=0; i<arr.size(); i++) {
        if (arr[i] == number) times++;
    }
    if (times >=(arr.size()/2+1)) return number;
    return -1;
}

} // namespace sword_finger_offer
