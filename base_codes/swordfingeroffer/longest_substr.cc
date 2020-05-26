#include <string>
#include <algorithm>
#include <unordered_set>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int longest_substr(std::string str) {
    if (str.length()<2) return str.length();
    int len = str.length();
    int start = 0;
    int end = 0;
    int result = 0;
    std::unordered_set<char> set;
    while(end < len) {
        while(set.count(str[end]) > 0){
            set.erase(str[start]);
            start++;
        }
        set.insert(str[end]);
        result = result > end - start +1 ? result: end - start + 1;
        end++;
    }
    return result;
}

int longest_substr_v2(std::string str) {
    if (str.length()<2) return str.length();
    int len = str.length();
    int position[26];
    std::fill_n(position, 26, -1);
    int curr = 0;
    int result = INT32_MIN;
    for (int i=0; i<len; i++) {
        if (position[str[i]-'a']>=0 && i - position[str[i]-'a'] <= curr) {
            curr = i - position[str[i]-'a'];
        }
        else {
            curr++;
        }
        result = std::max(result, curr);
        position[str[i]-'a'] = i;
    }
    return result;
}

} // namespace sword_finger_offer
