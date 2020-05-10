#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool check_binary_search_tree_order(std::vector<int>& vec) {
    return check_bst_dfs(vec, 0, vec.size()-1);
}

bool check_bst_dfs(std::vector<int>& vec, int begin, int end) {
    if (begin >= end) return true;
    int mid = begin;
    while(vec[mid] < vec[end]) mid++;
    for (int i=mid; i<end; i++) {
        if (vec[i] <= vec[end]) return false;
    }
    return check_bst_dfs(vec, begin, mid-1) && check_bst_dfs(vec, mid, end-1);
}

} // namespace sword_finger_offer
