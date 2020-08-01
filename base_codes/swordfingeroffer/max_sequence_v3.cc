#include <vector>
#include <list>
#include <set>
#include <iostream>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::vector<int> max_sequence_v3(std::vector<int>& arr, int windows) {
    std::vector<int> result;
    if (arr.size() < windows) return result;
    std::list<int> winds;
    for (int i=0; i<windows-1; i++) {
        while (!winds.empty() && arr[winds.back()] <= arr[i]) {
            winds.pop_back();
        }
        winds.push_back(i);
    }

    for (int i=windows-1; i<arr.size(); i++) {
        while (!winds.empty() && arr[winds.back()] <= arr[i]) winds.pop_back();
        winds.push_back(i);
        result.push_back(arr[winds.front()]);
        if (i - winds.front() +1 >=windows) winds.pop_front();
    }
    return result;
}

std::vector<int> max_sequence_v4(std::vector<int>& arr, int windows) {
    std::vector<int> result;
    if (arr.size() < windows) return result;
    std::multiset<int, std::greater<int>> mt;
    for (int i=0; i<windows-1; i++) mt.insert(arr[i]);
    for (int i=windows-1; i<arr.size(); i++) {
        mt.insert(arr[i]);

        for (auto iter=mt.begin(); iter !=mt.end(); iter++) std::cout << *iter << " ";
        std::cout << std::endl;

        result.push_back(*mt.begin());
        mt.erase(arr[i-windows+1]);
    }
    return result;
}

} // namespace sword_finger_offer
