#include <string>
#include <unordered_map>

#include "../binary_pointer.h"

namespace binary_pointer
{

std::string minWindow_v2(std::string s, std::string t) {
    if (s.length()<t.length() || t.length()==0) return "";
    int final_left = -1;
    int len = INT32_MAX;
    std::unordered_map<char, int> mp;
    for (int i=0; i<t.length(); i++) mp[t[i]]++;
    int count = mp.size();
    int full_count = 0;
    int curr_left = 0;
    for (int i=0; i<s.length(); i++) {
        if (mp.find(s[i])== mp.end()) continue;
        mp[s[i]]--;
        if (mp[s[i]]==0) {
            full_count++;
        }
        while (full_count == count)
        {
            if (i-curr_left+1 < len) {
                len = i-curr_left+1;
                final_left = curr_left;
            }
            if(mp.find(s[curr_left])!=mp.end()) {
                if (mp[s[curr_left]] == 0) full_count--;
                mp[s[curr_left]]++;
            }
            curr_left++;
        }
    }
    if (len == INT32_MAX) return "";
    return s.substr(final_left, len);
}

} // namespace binary_pointer
