#include <string>
#include <vector>
#include <stack>
#include "../stack_algs.h"

namespace stack_algs
{

std::vector<std::string> splitstr(std::string& path) {
    std::vector<std::string> result;
    if (path.length()==0) return result;
    int pre_idx = 0;
    for (int i=1; i<path.length(); i++) {
        if (path[i]=='/') {
            result.push_back(path.substr(pre_idx+1, i-pre_idx-1));
            pre_idx = i;
        }
    }
    if (path[path.length()-1]!='/') {
        result.push_back(path.substr(pre_idx+1));
    }
    return result;
}

std::string simplepath(std::string& path) {
    if (path.length()==0) return "";
    std::vector<std::string> items = splitstr(path);
    if (items.size()==0) return "/";
    std::string result;
    std::stack<std::string> s;
    for (int i=0; i<items.size(); i++) {
        if (items[i] =="." || items[i] == "")  continue;
        if (items[i] == ".." && s.empty() == false) s.pop();
        else {
            s.push(items[i]);
        }
    }
    while(!s.empty()) {
        result = "/" + s.top() + result;
        s.pop();
    }
    return result;
}

} // namespace stack_algs
