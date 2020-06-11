#include <string>
#include<algorithm>
#include <unordered_set>
#include "../binary_pointer.h"

// int binary_pointer::lengthOfLongestSubstring(std::string s) {
//     if (s.length()==0) return 0;
//     std::unordered_set<char> set;
//     int left=0;
//     int result = 0;
//     for (int i=0; i<s.length(); i++) {
//         if (set.find(s[i])!=set.end()) {
//             while(set.find(s[i])!=set.end()) {
//                 set.erase(s[left]);
//                 left++;
//             }
//         }
//         set.insert(s[i]);
//         result = std::max(result, i-left+1);
//     }
//     return result;
// }

int binary_pointer::lengthOfLongestSubstring(std::string s) {
    int n = s.length();
    if(n<2) return n;
    int start=0;
    int result=0;
    std::unordered_set<char> set;
    for (int i=0; i<n; i++) {
        if (set.find(s[i])!=set.end()) {
            while(set.find(s[i])!=set.end()) {
                set.erase(s[start]);
                start++;
            }
        }
        set.insert(s[i]);
        result = std::max(result, i - start +1);
    }
    return result;
}


int binary_pointer::lengthOfLongestSubstring_v2(std::string s) {
    int len = s.length();
    if (len <=1) return len;
    std::unordered_set<char> st;
    int begin=0;
    int result = -1;
    for (int i=0; i < len; i++) {
        while( !st.empty() && st.count(s[i]) > 0) {
            st.erase(s[begin]);
            begin++;
        }
        st.insert(s[i]);
        int tmp = i - begin + 1;
        result = result > tmp ? result : tmp;
    }
    return result;
}