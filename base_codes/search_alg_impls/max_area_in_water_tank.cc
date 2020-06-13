#include <cstdio>
#include <vector>
#include <algorithm>

#include "../search_algs.h"

int search::get_max_area(std::vector<int>& heights, std::vector<int>& idxs, int curr_idx) {
    int result = 0;
    for (int i=idxs.size()-1; i>=0; i--) {
        // if (heights[curr_idx] <= heights[idxs[i]]) {
        //     int curr = (curr_idx - idxs[i]) * heights[curr_idx];
        //     result = result > curr ? result : curr;
        // }
        // else {
        //     break;
        // }
        int curr = (curr_idx - idxs[i]) * std::min(heights[curr_idx], heights[idxs[i]]);
        result = std::max(result, curr);
    }
    return result;
}

int search::maxArea(std::vector<int>& heights) {
    if(heights.size() < 2) return 0;

    int result = 0;

    std::vector<int> left_bar;
    left_bar.push_back(0);
    for (int i=1; i < heights.size(); i++) {
        if (heights[i] > heights[left_bar.back()]) {
            left_bar.push_back(i);
        }
        else {
            int curr = get_max_area(heights, left_bar, i);
            result = result>curr? result: curr;
        }
    }

    for (int i=0; i<left_bar.size(); i++) {
        int curr = heights[left_bar[i]]  * (left_bar.back() - left_bar[i]);
        result = result>curr?result:curr;
    }

    return result;
}

int search::maxArea_v2(std::vector<int>& height) {
    if (height.size() < 2)  return 0;

    int res = 0;
    for (int i=0, j=height.size()-1; i<j; ) {
        int min_height = height[i] < height[j] ? height[i++] : height[j--];
        int curr = min_height * (j - i +1);
        res = res > curr ? res : curr;
    }
    return res;
}


int search::maxArea_v3(std::vector<int>& height) {
    if (height.size()<2) return 0;
    // if (height.size()==2) return std::min(height[0], height[1]);
    int left = 0;
    int right = height.size() -1;
    int result = 0;
    while(left < right) {
        int curr_area = std::min(height[left], height[right]) * (right - left);
        result = std::max(result, curr_area);
        if (height[left] < height[right]) {
            left++;
        }
        else {
            right--;
        }
    }
    return result;
}