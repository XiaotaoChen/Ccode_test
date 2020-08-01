#include <vector>
#include <algorithm> // make heap
#include <set>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

float median_number_V2(std::vector<int>& arr) {
    int count = 0;
    std::vector<int> max_heap;
    std::vector<int> min_heap;
    for (int i=0; i<arr.size(); i++) {
        count++;
        int num = arr[i];
        if (i%2 == 0) {
            if (!min_heap.empty() && min_heap.front() < num) {
                min_heap.push_back(num);
                std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
                num = min_heap.front();
                std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
                min_heap.pop_back();
            }
            max_heap.push_back(num);
            std::push_heap(max_heap.begin(), max_heap.end(), std::less<int>());
        }
        else {
            if (!max_heap.empty() && max_heap.front() > num) {
                max_heap.push_back(num);
                std::push_heap(max_heap.begin(), max_heap.end(), std::less<int>());
                num = max_heap.front();
                std::pop_heap(max_heap.begin(), max_heap.end(), std::less<int>());
                max_heap.pop_back();
            }
            min_heap.push_back(num);
            std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
        }
    }
    if (count %2 == 1) return max_heap.front();
    else return float(max_heap.front() + min_heap.front())/2;
}


float median_number_V3(std::vector<int>& arr) {
    int count = 0;
    std::multiset<int> min_heap;
    std::multiset<int, std::greater<int>> max_heap;
    for (int i=0; i<arr.size(); i++) {
        count++;
        int num = arr[i];
        if (i%2==0) {
            if (!min_heap.empty() && num > (*min_heap.begin())) {
                min_heap.insert(num);
                num = *min_heap.begin();
                min_heap.erase(num);
            }
            max_heap.insert(num);
        }
        else {
            if (!max_heap.empty() && num < (*max_heap.begin())) {
                max_heap.insert(num);
                num = *max_heap.begin();
                max_heap.erase(num);
            }
            min_heap.insert(num);
        }
    }
    if (count %2 ==1) return *max_heap.begin();
    else return float(*max_heap.begin() + *min_heap.begin()) /2 ;
}


} // namespace sword_finger_offer
