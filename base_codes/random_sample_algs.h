#ifndef RANDOM_SAMPLE_ALG_
#define RANDOM_SAMPLE_ALG_

#include "data_structs/base_struct.h"
namespace random_sample_alg
{

// https://leetcode-cn.com/problems/linked-list-random-node/
class Solution {
public:
    Solution(ListNode* head);
    /** Returns a random node's value. */
    int getRandom();
private:
    ListNode* root;
};

// https://leetcode-cn.com/problems/random-pick-index/
int pick_idx(std::vector<int>& nums, int target);

} // namespace random_sample_alg



#endif