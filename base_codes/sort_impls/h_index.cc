#include <vector>
#include <algorithm>
#include <queue>

#include "../sorts.h"

namespace sort
{

int comp(const void* a, const void* b) {
    return *((int*)a) - *((int*)b);
}

bool comp2(int& a, int& b) {
    return a > b;
}

int h_index(std::vector<int>& citations) {
    if (citations.size()==0) return 0;
    // std::qsort(&citations[0], citations.size(), sizeof(int), comp);
    std::sort(citations.begin(), citations.end());

    int idx=citations.size()-1;
    int size = citations.size();
    int h_idx = 0;
    while(idx >=0 && size - idx <= citations[idx]) {
        int tmp = size - idx;
        h_idx = citations[idx] < tmp ? citations[idx] : tmp;
        idx--;
    }

    return h_idx;
}

int h_index_v2(std::vector<int>& citations) {
    if (citations.size()==0) return 0;
    std::priority_queue<int, std::vector<int>, std::less<int>> pq(citations.begin(),citations.end());
    int ans = 0;
    while(!pq.empty()) {
        int tmp = pq.top(); pq.pop();
        if (tmp >ans) {
            ans++;
        }
        else {
            break;
        }
    }
    return ans;
}

} // namespace sort
