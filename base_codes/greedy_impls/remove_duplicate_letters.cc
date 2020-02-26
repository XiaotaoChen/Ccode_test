#include<string>
#include<vector>
#include "../greedy_algs.h"


// wrong
std::string greedy::removeDuplicateLetters_wrong(std::string s) {
    if (s.length() < 2) return s;
    std::vector<char> result;
    for (int i=s.length()-1; i>=0; i--) {
        int duplicate_idx = -1;
        for (int j=0; j<result.size(); j++) {
            if (s[i] ==  result[j]){
                duplicate_idx = j;
                break;
            }
        }
        if (duplicate_idx != -1) {
            if (result[0] > s[i]) {
                // erase i item
                result.erase(result.begin() + duplicate_idx);
                result.insert(result.begin(), s[i]);
            }
        }
        else {
            result.insert(result.begin(), s[i]);
        }
    }
    std::string res = "";
    for (int i=0; i<result.size(); i++) res += result[i];
    return res;
}

std::string greedy::removeDuplicateLetters(std::string s) {
    if (s.length()<2) return s;
    std::string result = "";
    for (int i=0; i<s.length(); i++) {
        if (result.find(s[i]) != std::string::npos) continue; 
        while(!result.empty() && result.back() > s[i] && s.find(result.back(), i) != std::string::npos) {
            result.pop_back();
        }
        result.push_back(s[i]);
    }
    return result;
}