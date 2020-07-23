#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../hot_100.h"

namespace hot_100
{

int leastInterval(std::vector<char>& tasks, int n) {
    if (tasks.size()==0) return 0;
    std::unordered_map<char, int> up;
    int m = tasks.size();
    for (int i=0; i<m; i++) up[tasks[i]]++;
    int max_count = 0;
    for (auto p: up) {
        if (p.second > max_count) max_count = p.second;
    }
    int final_left = 0;
    for (auto p: up) {
        if (p.second==max_count) final_left++;
    }
    return m > (n+1)*(max_count-1)+final_left ? m: (n+1)*(max_count-1)+final_left;
}

} // namespace hot_100
