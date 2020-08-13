#include <vector>

namespace thot_50
{

int longestIncreasingPath(std::vector<std::vector<int> >& matrix);

// https://leetcode-cn.com/problems/reverse-integer/
int reverse(int x);

// https://leetcode-cn.com/problems/permutations/
std::vector<std::vector<int> > permute(std::vector<int>& nums);
std::vector<std::vector<int> > permute_v2(std::vector<int>& nums);

std::vector<std::string> legal_partness(int n);

// https://leetcode-cn.com/problems/subsets/
std::vector<std::vector<int> > subsets(std::vector<int>& nums);

std::vector<std::vector<int> > subsets_v2(std::vector<int>& nums);

// https://leetcode-cn.com/problems/super-egg-drop/
int superEggDrop(int K, int N);
int superEggDrop_v2(int K, int N);
int superEggDrop_v3(int K, int N);

} // namespace thot_50
