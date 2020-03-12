#ifndef GREED_ALG_
#define GREED_ALG_

#include<vector>
#include <string>

namespace greedy {

// https://leetcode-cn.com/problems/advantage-shuffle/
std::vector<int> advantageCount(std::vector<int>& A, std::vector<int>& B);


// https://leetcode-cn.com/problems/jump-game/
bool canJump(std::vector<int>& nums);

// https://leetcode-cn.com/problems/jump-game-ii/
int jump(std::vector<int>& nums);

// https://leetcode-cn.com/problems/gas-station/
int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost);
int canCompleteCircuit_v2(std::vector<int> &gas, std::vector<int> &cost);

// https://leetcode-cn.com/problems/wildcard-matching/
bool isMatch(std::string s, std::string p);

// https://leetcode-cn.com/problems/remove-duplicate-letters/
std::string removeDuplicateLetters(std::string s);
std::string removeDuplicateLetters_wrong(std::string s);

}

#endif // GREED_ALG_