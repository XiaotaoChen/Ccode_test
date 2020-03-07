#include <unordered_map>

#include "../binary_pointer.h"

std::string binary_pointer::minWindow(std::string s, std::string t) {
    std::unordered_map<char, int> map;
    for (int i=0; i<t.length(); i++) {
        map[t[i]]++ ;
    }

    int map_size = map.size();

    std::string result = "";
    int curr_len = INT32_MAX;
    int left = 0;
    int right = 0;
    int match = 0;
    for (int i=0; i<s.length(); i++) {
        if (map.find(s[i]) != map.end()) {
            map[s[i]]--;
            if (map[s[i]] == 0) match++;
            if (match==map_size) {
                right = i;
                while(left <= right && match==map_size) {
                    if (right-left +1<curr_len) {
                        curr_len = right-left +1;
                        result = s.substr(left, curr_len);
                    }
                    if (map.find(s[left])!=map.end()) {
                        map[s[left]] ++;
                        if (map[s[left]] > 0) match--;
                    }
                    left++;
                }
            }
        }
    }
    return result;
}