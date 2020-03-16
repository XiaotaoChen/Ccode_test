#include <vector>
#include <string>
#include <unordered_map>

#include "../bits_algs.h"

std::vector<std::string> bits_alg::findRepeatedDnaSequences(std::string s) {
    std::vector<std::string> result;
    int len = s.length();
    if (len < 10) return result;
    std::unordered_map<char, int> char2num = {{'A',0},{'C',1},{'G',2},{'T',3}};

    std::unordered_map<int, int> map;
    int curr = 0;
    for (int i=0; i<9; i++) {
        curr = curr<<2;
        curr = curr | char2num[s[i]];
    }
    // map[curr] = s.substr(0, 10);
    int max_val = 0x000fffff;
    for (int i=9; i<len; i++) {
        curr = curr<<2;
        curr = curr | char2num[s[i]];
        curr = curr & max_val;
        if (map.find(curr)!=map.end()) {
            map[curr]++;
            if (map[curr]==2) result.push_back(s.substr(i-9, 10));
        }
        else {
            map[curr] = 1;
        }
    }
    return result;
}