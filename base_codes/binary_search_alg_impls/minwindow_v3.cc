#include <string>
#include <unordered_map>
#include "../binary_pointer.h"

namespace binary_pointer
{

std::string minWindow_v3(std::string s, std::string t) {
    if (s.length() < t.length()) return "";
    std::unordered_map<char, int> ump;
    for (int i=0; i<t.length(); i++) {
        ump[t[i]]++;
    }
    int unique_cnt = ump.size();

    int left = 0;
    int len = INT32_MAX;
    int curr = 0;
    for (int i=0; i<s.length(); i++) {
        if (ump.find(s[i])!=ump.end()) {
            ump[s[i]]--;
            if (ump[s[i]]==0) unique_cnt--;
            if (unique_cnt==0) {
                while(unique_cnt==0) {
                    if (ump.find(s[curr])!=ump.end()) {
                        if (ump[s[curr]] == 0) unique_cnt++;
                        ump[s[curr]]++;
                    }
                    curr++;
                }
                if (len > i - curr +2) {
                    len = i - curr +2;
                    left = curr;
                }
            }
        }
    }
    if (len == INT32_MAX) return "";
    return s.substr(left-1, len);
}

} // namespace binary_pointer
