#ifndef MERGE_SET_ALG_
#define MERGE_SET_ALG_

#include <vector>
#include <unordered_map>


namespace merge_set {

//https://leetcode-cn.com/problems/surrounded-regions/
void solve(std::vector<std::vector<char>>& board);

// https://leetcode-cn.com/problems/number-of-islands/
int numIslands(std::vector<std::vector<char>>& grid);

// https://leetcode-cn.com/problems/longest-consecutive-sequence/
int longestConsecutive(std::vector<int>& nums);
int find_root(std::unordered_map<int,int>& nums, int x);
int merge_two_set(std::unordered_map<int,int>& nums, int x, int y, std::unordered_map<int,int>& cnts);
int longestConsecutive_v2(std::vector<int>& nums);

int longestConsecutive_V3(std::vector<int>& nums);
int longestConsecutive_V4(std::vector<int>& nums);

}


#endif