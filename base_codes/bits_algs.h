#include <vector>
#include <string>

namespace bits_alg
{

// https://leetcode-cn.com/problems/subsets/
std::vector<std::vector<int>> subsets(std::vector<int>& nums);
void trace_back_subset(std::vector<std::vector<int>>& combinations, std::vector<int> curr, std::vector<int>& nums, int idx);

std::vector<std::vector<int>> subsets_v2(std::vector<int>& nums);

// https://leetcode-cn.com/problems/repeated-dna-sequences/
std::vector<std::string> findRepeatedDnaSequences(std::string s);

// https://leetcode-cn.com/problems/single-number/
int singleNumber(std::vector<int>& nums);

} // namespace bits_alg

