#include <string>
#include <vector>
#include <stack>
#include "../search_algs.h"

namespace search
{

std::vector<std::string> split_str_V2(std::string path) {
    std::vector<std::string> result;
    int pre = 0;
    for (int i=1; i<path.length(); i++) {
        if(path[i] == '/') {
            if (i-pre > 1) result.push_back(path.substr(pre+1, i-pre-1));
            pre = i;
        }
    }
    if (pre!=path.length()-1) {
        result.push_back(path.substr(pre+1, path.length() - pre-1));
    }
    return result;
}

std::string simplifyPath_V2(std::string path) {
    if (path.length()==0) return "/";
    std::vector<std::string> items = split_str_V2(path);
    if (items.size()==0) return "/";
    std::stack<std::string> st;
    for (int i=0; i<items.size(); i++) {
        if (items[i]==".") continue;
        if (items[i]== ".."){
            if (!st.empty()) st.pop();
        }
        else {
            st.push(items[i]);
        }
    }
    
    if (st.empty()) return "/";

    std::string result;
    while(!st.empty()) {
        result = "/" + st.top() + result; st.pop();
    }
    return result;
}   

} // namespace search
