#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>

#include "../search_algs.h"

namespace search
{

std::unordered_map<char, int> get_ch_map(std::string& str) {
    std::unordered_map<char, int> map;
    for (auto ch : str) map[ch]++;
    return map;
}

std::map<char, int> get_ch_map2(std::string& str) {
    std::map<char, int> map;
    for (auto ch : str) map[ch]++;
    return map;
}

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> result;

    // std::unordered_map<std::unordered_map<char, int>, std::vector<std::string>> map;
    std::map<std::map<char, int>, std::vector<std::string>> map;

    for (int i=0; i<strs.size(); i++) {
        // std::unordered_map<char, int> tmp_map = get_ch_map(strs[i]);
        std::map<char, int> tmp_map = get_ch_map2(strs[i]);

        map[tmp_map].push_back(strs[i]);
    }
    for (auto kv : map) {
        result.push_back(kv.second);
    }
    return result;
}


} // namespace search
 