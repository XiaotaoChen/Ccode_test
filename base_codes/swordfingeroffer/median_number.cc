#include <vector>
#include <algorithm>
#include <set>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int median_number(std::vector<int>& arr) {
    if (arr.size() == 0) return -1;
    if (arr.size() == 1) return arr[0];

    std::vector<int> max_heap;
    std::vector<int> min_heap;
    for (int i=0; i<arr.size(); i++) {
        int num = arr[i];
        if ((i & 1) == 0) {
            if (min_heap.size() >0 && min_heap[0] < num) {
                min_heap.push_back(num);
                std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
                num = min_heap[0];
                std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
                min_heap.pop_back();
            }
            max_heap.push_back(num);
            std::push_heap(max_heap.begin(), max_heap.end(), std::less<int>());
        }
        else {
            if (max_heap.size() >0 && max_heap[0] > num) {
                max_heap.push_back(num);
                std::push_heap(max_heap.begin(), max_heap.end(), std::less<int>());
                num = max_heap[0];
                std::pop_heap(max_heap.begin(), max_heap.end(), std::less<int>());
                max_heap.pop_back();
            }
            min_heap.push_back(num);
            std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
        }
    }

    if (arr.size() %2==1) return max_heap[0];
    return (max_heap[0]+min_heap[0])/2;
}

int median_number_with_set(std::vector<int>& arr) {
    if (arr.size() == 0) return -1;
    if (arr.size() == 1) return arr[0];

    std::multiset<int, std::greater<int>> max_heap;
    std::multiset<int, std::less<int>> min_heap;
    for (int i=0; i<arr.size(); i++) {
        int num = arr[i];
        if ((i&1) == 0) {
            if (min_heap.size() >0 && (*min_heap.begin()) < num) {
                min_heap.insert(num);
                num = (*min_heap.begin());
                min_heap.erase(min_heap.begin());
            }
            max_heap.insert(num);
        }
        else {
            if (max_heap.size() > 0 && (*max_heap.begin()) > num) {
                max_heap.insert(num);
                num = (*max_heap.begin());
                max_heap.erase(max_heap.begin());
            }
            min_heap.insert(num);
        }
    }
    if (arr.size()%2==1) return *max_heap.begin();
    return ((*max_heap.begin()) + (*min_heap.begin())) /2;

}

} // namespace sword_finger_offer
