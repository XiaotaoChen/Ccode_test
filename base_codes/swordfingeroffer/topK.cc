#include <vector>
#include <algorithm> // make_heap
#include <set>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::vector<int> TopKminus(std::vector<int>& arr, int k) {
    if (arr.size()==0 || arr.size() <= k) return arr;
    int begin = 0;
    int end = arr.size() -1;
    while(begin < end) {
        int idx = partition(arr, begin, end);
        if (idx == k) break;
        if (idx >k) end = idx-1;
        else begin = idx+1;
    }
    std::vector<int> result(arr.begin(), arr.begin() + k);
    return result;
}

// max heap
void heap_modify(std::vector<int>& arr, int begin, int end) {
    int parent = begin;
    int son = 2 * parent +1;
    while(son <=end) {
        if (son+1 < end && arr[son] < arr[son+1]) son++;
        if (arr[parent] >= arr[son]) return;
        swap<int>(arr[parent], arr[son]);
        parent = son;
        son = 2 * parent +1;
    }
}

std::vector<int> TopKminus_with_heap(std::vector<int>& arr, int k) {
    if (arr.size()==0|| arr.size() <= k) return arr;
    std::vector<int> result(arr.begin(), arr.begin()+k);
    // make heap
    int mid = k/2 -1;
    for (int i=mid; i>=0; i--) {
        heap_modify(result, i, k-1);
    }

    for (int i=k; i<arr.size(); i++) {
        if (arr[i] < result[0]) {
            // swap<int>(result[0], arr[i]);
            result[0] = arr[i];
            heap_modify(result, 0, k-1);
        }
    }
    return result;
}

std::vector<int> TopKminus_with_makeheap(std::vector<int>& arr, int k) {
    if (arr.size()==0|| arr.size() <= k) return arr;
    std::vector<int> result(arr.begin(), arr.begin()+k);
    std::make_heap(result.begin(), result.end());
    for (int i=k; i<arr.size(); i++) {
        if (arr[i]<result[0]) {
            // swap<int>(result[0], arr[i]);
            // result[0] = arr[i];
            // std::make_heap(result.begin(), result.end());
            std::pop_heap(result.begin(), result.end()); result.pop_back();
            result.push_back(arr[i]); std::push_heap(result.begin(), result.end());
        }
    }
    return result;
}

std::vector<int> TopKminus_with_set(std::vector<int>& arr, int k) {
    if (arr.size() == 0 || arr.size() <= k) return arr;
    std::multiset<int, std::greater<int>> set;
    for (int i=0; i < arr.size(); i++) {
        if (set.size() < k) set.insert(arr[i]);
        else if (arr[i] < *(set.begin())) {
            set.erase(set.begin());
            set.insert(arr[i]);
        }
    }
    std::vector<int> result(set.begin(), set.end());
    return result;
}


} // namespace sword_finger_offer
