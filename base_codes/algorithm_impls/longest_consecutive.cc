#include <algorithm> // max_element
#include <memory> // shared_memory
#include "../algorithm.h"

int longestConsecutive(vector<int> &num) {
    if (num.size() == 0) return 0;
    if (num.size() == 1) return 1;
    vector<int>::iterator max_num_iter;
    max_num_iter = std::max_element(num.begin(), num.end());

    int max_num = *max_num_iter;
    // int* arr = new int[max_num];
    int arr[max_num];
    // std::shared_ptr<int> shared_arr(new int[max_num]);
    // int* arr = shared_arr.get();
    for (int i=0; i< num.size(); i++) {
        arr[num[i]] = 1;
    }
    // longest consecutive
    int result = 0;
    bool flag = true;
    int curr = 0;
    for (int i=0; i<max_num; i++) {
        if(arr[i] == 1){
            curr++;
        }
        else {
            result = std::max(curr, result);
            curr = 0;
        }
    }
    // delete[] arr;
    return result;
}

int longestConsecutive_V2(vector<int> &num) {
    if (num.size()==0) return 0;
    unordered_set<int> num_set;
    for(int i=0; i<num.size(); i++) {
        if (num_set.find(num[i]) == num_set.end()) {
            num_set.insert(num[i]);
        }
    }
    int result = 0;
    for (int i=0; i<num.size(); i++) {
        if (num_set.find(num[i]) == num_set.end()) continue;
        int val = num[i];
        int curr = 0;
        while(num_set.find(val)!=num_set.end()) {
            num_set.erase(val);
            curr++;
            val--;
        }
        val = num[i] + 1;
        while(num_set.find(val) != num_set.end()) {
            num_set.erase(val);
            curr++;
            val++;
        }
        result = result >= curr? result: curr;
    }
    return result;
}
