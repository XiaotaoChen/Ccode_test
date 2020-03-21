#include <vector>
#include "../line_tree_algs.h"

namespace line_tree_alg
{

NumArray::NumArray(std::vector<int>& nums): nums(&nums), sums(std::vector<int>(nums.size()<<2, 0)), n(nums.size()) {
    if (n>0) build(1, 0, n-1);
}

void NumArray::build(int root, int left , int right) {
    if (left == right) {
        sums[root] = (*nums)[left];
        return;
    }
    int mid = (left + right)>>1;
    build(root<<1, left, mid);
    build(root<<1|1, mid+1, right);
    sums[root] = sums[root<<1] + sums[root<<1|1];
}

void NumArray::modify(int root, int left, int right, int idx, int val) {
    if (left==right) {
        sums[root] = val;
        return;
    }
    int mid = (left + right) >>1;
    if (idx<=mid) modify(root<<1, left, mid, idx, val);
    else modify(root<<1|1, mid+1, right, idx, val);
    sums[root] = sums[root<<1] + sums[root<<1|1];
    
}

int NumArray::query(int root, int left, int right, int x, int y) {
    if (x<=left && y>=right) return sums[root];
    int mid = (left+right) >>1;
    int ans = 0;
    if (x <=mid) ans+= query(root<<1, left, mid, x, y);
    if (y>mid) ans+= query(root<<1|1, mid+1, right, x, y);
    return ans;
}


void NumArray::update(int i, int val) {
    modify(1, 0, n-1, i, val);
}

int NumArray::sumRange(int i, int j) {
    return query(1, 0, n-1, i, j);
}


} // namespace line_tree_alg


