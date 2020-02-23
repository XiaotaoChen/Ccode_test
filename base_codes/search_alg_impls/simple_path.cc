#include<cstdio>
#include<string>
#include<stack>
#include<vector>
#include<algorithm> // std::reverse

#include "../search_algs.h"

std::vector<std::string> search::splitstr(std::string path) {
    std::vector<std::string> result;
    int pre = 0;
    int i = 1;
    for (i=1; i<path.length(); i++) {
        if (path[i] == '/') {
            result.push_back(path.substr(pre+1, i-pre-1));
            pre = i;
        }
    }
    if (pre != path.length() -1) {
        result.push_back(path.substr(pre+1, path.length()-pre-1));
    }
    return result;
}

std::string search::simplifyPath(std::string path) {
    std::vector<std::string> items = splitstr(path);
    std::stack<std::string> s;
    for (int i=0; i<items.size(); i++) {
        if (items[i] == "" || items[i] == ".") continue;
        if (items[i] == "..") {
            if (!s.empty()) s.pop();
        }
        else {
            s.push(items[i]);
        }
    }

    if (s.empty()) {
        return "/";
    }

    std::string result = "";
    while(!s.empty()) {
        result = '/' + s.top() + result;
        s.pop();
    }
    // std::reverse(result.begin(), result.end());
    return result;
}