#include <vector>
#include <string>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

void permutation_dfs(std::vector<std::string>& commbinations, std::string& str, int idx) {
    if (idx==str.length()-1) {
        commbinations.push_back(str);
        return;
    }
    for (int i=idx; i<str.length(); i++) {
        swap<char>(str[idx], str[i]);
        permutation_dfs(commbinations, str, idx+1);
        swap<char>(str[idx], str[i]);
    }
}

std::vector<std::string> permutation(std::string str) {
    std::vector<std::string> result;
    if (str.length()==0) return result;
    permutation_dfs(result, str, 0);
}

void combination_dfs(std::vector<std::string>& comb, std::string& str, int idx) {
    if (idx==str.length()) return;
    int size = comb.size();
    comb.push_back(str.substr(idx, 1));
    for (int i=0; i<size; i++) {
        std::string tmp = comb[i] + str[idx];
        comb.push_back(tmp);
    }
    combination_dfs(comb, str, idx+1);
}

std::vector<std::string> combinations(std::string str) {
    std::vector<std::string> result;
    if (str.length() == 0) return result;
    combination_dfs(result, str, 0);
    return result;
}

bool condition_func(std::vector<int>& arr) {
    if (arr[0]+arr[1]+arr[2]+arr[3] == arr[4]+arr[5]+arr[6]+arr[7] && 
        arr[0]+arr[1]+arr[4]+arr[5] == arr[2]+arr[3]+arr[6]+arr[7] &&
        arr[0]+arr[2]+arr[4]+arr[6] == arr[1]+arr[3]+arr[5]+arr[7]) return true;
    return false;
}

bool eight_queen_check(std::vector<int>& arr) {
    for (int i=0; i < arr.size()-1; i++) {
        for (int j=i+1; j<arr.size(); j++) {
            if (arr[j]-arr[i] == j-i || arr[j]-arr[i] == i -j) {
                return false;
            }
        }
    }
    return true;
}


void permut_dfs(std::vector<std::vector<int>> & commbinations, std::vector<int>& curr, int idx, bool(*func)(std::vector<int>&) ) {
    if (idx >= curr.size()) return;
    if (idx==curr.size()-1) {
        if (func(curr)) commbinations.push_back(curr);
    }

    for (int i=idx; i < curr.size(); i++) {
        swap<int>(curr[idx], curr[i]);
        permut_dfs(commbinations, curr, idx+1, func);
        swap<int>(curr[idx], curr[i]);
    }
}

std::vector<std::vector<int>> queen_permutation(int num) {
    std::vector<int> arr(num);
    for (int i=0; i<num; i++) arr[i] = i;
    std::vector<std::vector<int>> result;
    // permut_dfs(result, arr, 0, eight_queen_check);
    permut_dfs(result, arr, 0, condition_func);
    return result;
}


} // namespace sword_finger_offer
