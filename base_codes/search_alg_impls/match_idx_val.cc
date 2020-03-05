#include <cstdio>
#include <vector>
#include "../search_algs.h"

void search::match_idx_val(std::vector<int>& vec, std::vector<int>& result, int left, int right) {
    if (left > right) return;
    if (left == right) {
        if (vec[left] == left) {
            result.push_back(left);
        }
        return;
    }

    int mid = (left + right) /2;
    if (vec[mid] == mid) {
        result.push_back(mid);
    }

    // search mid --> right
    match_idx_val(vec, result, mid+1, right);
    if (vec[mid] >= mid) {
        match_idx_val(vec, result, left, mid -1);
    }
    return;
}

void search::match_idx_val_v2(std::vector<int>& vec, std::vector<int>& result, int left, int right) {
    if (left > right) return;
    int mid = (left + right) /2;
    if (vec[mid] == mid) {
        result.push_back(mid);
        int idx = mid-1;
        while(idx>=0 && vec[idx]==idx) {
            result.push_back(idx);
            idx--;
        }
        idx = mid+1;
        while(idx<=right && vec[idx] == idx) {
            result.push_back(idx);
            idx++;
        }
        // match_idx_val(vec, result, left, mid -1);
        // match_idx_val(vec, result, mid+1, right);
    }
    else if (vec[mid] > mid) {
        match_idx_val(vec, result, left, mid -1);
    }
    else {
        // search mid --> right
        match_idx_val(vec, result, mid+1, right);
    }
    return;
}