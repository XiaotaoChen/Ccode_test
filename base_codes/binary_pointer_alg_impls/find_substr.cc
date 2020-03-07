#include <vector>
#include <unordered_map>
#include <string>

#include "../binary_pointer.h"

bool binary_pointer::is_ok(std::string s, int start, std::unordered_map<std::string, int> map, int word_len, int words_num) {
    int match=0;
    if (start + words_num * word_len-1>s.length()) return false;
    for (int i=0;i<words_num; i++) {
        int begin = start + word_len * i;
        std::string substr = s.substr(begin, word_len);
        if (map.find(substr)== map.end()) return false;
        map[substr]--;
        if (map[substr]==0) match++;
        else if (map[substr]<0) return false;
    }
    if (match==map.size()) return true;
    return false;
}

std::vector<int> binary_pointer::findSubstring(std::string s, std::vector<std::string>& words) {
    std::vector<int> result;
    if (s.length()==0||words.size()==0) return result;
    std::unordered_map<std::string, int> map;
    for (int i=0; i<words.size(); i++) map[words[i]]++;
    int words_num = words.size();
    int word_len = words[0].size();
    for (int i=0; i<s.length()-word_len+1;i++) {
        std::string substr = s.substr(i, word_len);
        if (map.find(substr)!=map.end()) {
            bool flag = is_ok(s, i, map, word_len, words_num);
            if (flag) result.push_back(i);
        }
    }
    return result;
}

std::vector<int> binary_pointer::findSubstring_v2(std::string s, std::vector<std::string>& words) {
    std::vector<int> result;
    if (s.length()==0||words.size()==0) return result;
    
    std::unordered_map<std::string, int> map;
    for (int i=0; i<words.size(); i++) map[words[i]]++;
    
    int word_nums = words.size();
    int word_len = words[0].length();
    for (int i=0; i<word_len; i++) {
        int left = i;
        int match = 0;
        std::unordered_map<std::string, int> tmp_map(map);
        for (int j=i; j<s.length()-word_len+1; j+=word_len) {
            std::string substr = s.substr(j, word_len);
            if (tmp_map.find(substr)!=tmp_map.end()) {
                tmp_map[substr]--;
                if (tmp_map[substr]==0) match++;
                while(match==map.size()) {
                    if (j-left+word_len == word_len*word_nums) result.push_back(left);
                    std::string tmp = s.substr(left, word_len);
                    if (tmp_map.find(tmp)!=tmp_map.end()) {
                        tmp_map[tmp]++;
                        if (tmp_map[tmp]>0) match--;
                    }
                    left += word_len;
                }
            }
        }
    }
    return result;
}