#include <vector>
#include <string>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

template<typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

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


} // namespace sword_finger_offer
