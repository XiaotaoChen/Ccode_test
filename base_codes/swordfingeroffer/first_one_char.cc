#include <string>
#include <map>
#include <unordered_map>
#include <iostream>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

char first_one_char(std::string& str) {
    if (str.length()==0) return '#';
    int cnt[256];
    std::fill_n(cnt, 256, 0);
    for (int i=0; i<str.length(); i++) {
        cnt[str[i]]++;
    }
    for (int i=0; i<str.length(); i++) {
        if (cnt[str[i]] == 1) return str[i];
    }
    return '#';
}

char first_one_char_v2(std::string& str) {
    if (str.length()==0) return '#';
    // std::map<char, int, std::less<char>> mp;
    std::unordered_map<char, int> mp;
    for (int i=0; i<str.length(); i++) {
        mp[str[i]]++;
    }
    for (auto pr: mp) {
        std::cout << pr.first << ":" << pr.second << ", count: " << mp.count(pr.first) << std::endl;
    }
    for (int i=0; i<str.length(); i++) {
        if (mp[str[i]]==1) return str[i];
    }
    return '#';
}

char first_one_char_v3(std::string& str) {
    if (str.length() == 0) return '#';
    std::unordered_map<char, int> mp;
    int curr=0;
    for (int i=0; i<str.length(); i++) {
        // if (mp.count(str[curr])<=1) {
        //     mp[str[i]]++;
        //     continue;
        // }
        mp[str[i]]++;
        while(mp.size() >0 && mp[str[curr]]>=2) {
            curr++;
        }
    }
    if (curr == str.length()) return '#';
    return str[curr];
}

} // namespace sword_finger_offer
