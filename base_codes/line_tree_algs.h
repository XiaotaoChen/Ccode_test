#ifndef LINE_TREE_ALGS_
#define LINE_TREE_ALGS_

#include <vector>

namespace line_tree_alg
{
    
// https://leetcode-cn.com/problems/the-skyline-problem/
std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings);

// https://leetcode-cn.com/problems/range-sum-query-mutable/
class NumArray {
private:
    std::vector<int> sums;
    std::vector<int>* nums;
    int n;

public:
    NumArray(std::vector<int>& nums);

    void build(int root, int left, int right);

    void modify(int root, int left, int right, int idx, int val);

    int query(int root, int left, int right, int x, int y);

    void update(int i, int val);
    
    int sumRange(int i, int j);

};

} // namespace line_tree_alg



#endif