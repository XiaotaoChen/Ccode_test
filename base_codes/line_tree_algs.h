#ifndef LINE_TREE_ALGS_
#define LINE_TREE_ALGS_

#include <vector>
#include "data_structs/base_struct.h"

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

class NumArray_v2 {
private:
    std::vector<int> sums;
    std::vector<int>* nums;
    int n;

public:
    NumArray_v2(std::vector<int>& nums);

    int lowbit(int x) ;

    void update(int i, int val);
    
    int sumRange(int i, int j);

};

class NumArray_v3 {
private:
    std::vector<int>* nums;
    int n;
    SegNode* root;

public:
    NumArray_v3(std::vector<int>& nums);
    void create_line_tree(std::vector<int>& nums, SegNode*& root, int left, int right);
    void update_line_tree(SegNode* root, int idx, int val);
    int sum_range_line_tree(SegNode* root, int left, int right);
    void update(int idx, int val);
    int sumRange(int i, int j);
};

void update(std::vector<int>& BIT, int index, int val);

int query(std::vector<int>& BIT, int index);

int reversePairs(std::vector<int>& nums);

} // namespace line_tree_alg



#endif