#ifndef SEARCH_ALG_
#define SEARCH_ALG_

#include<string>
#include<unordered_set>
#include<map>

#include "data_structs/base_struct.h"

namespace search {

bool is_one_diff(const std::string& str1, const std::string& str2);

// https://www.nowcoder.com/practice/bd75ae43ff7148548eb4701550df2714?tpId=46&tqId=29054&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
int ladderLength(std::string start, std::string end, std::unordered_set<std::string> &dict);

std::vector<std::vector<std::string> > findLadders(std::string start, std::string end, std::unordered_set<std::string> &dict);

void generate(std::map<std::string, std::vector<std::string> > &path_map, std::string& start, std::string& end,
                                                std::vector<std::string>& tmp_path, std::vector<std::vector<std::string> >& result);

// https://www.nowcoder.com/practice/2064017fd87048f0858ec5ba6772343c?tpId=46&tqId=29053&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
std::vector<std::vector<std::string> > findLadders_V2(std::string start, std::string end, std::unordered_set<std::string> &dict);

bool is_char_num(char ch);

std::string keep_char_num(std::string str);

// https://www.nowcoder.com/practice/b4dc0f1ee20448fca1f387fb1546f43f?tpId=46&tqId=29055&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
bool isPalindrome(std::string s); 

namespace binary_tree {
    // https://www.nowcoder.com/practice/da785ea0f64b442488c125b441a4ba4a?tpId=46&tqId=29056&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
    int maxPathSum(TreeNode *root);
    int maxPathSum_dfs(TreeNode *root, int &result);
}

int maxProfit(std::vector<int> &prices);

// https://www.nowcoder.com/practice/572903b1edbd4a33b2716f7649b4ffd4?tpId=46&tqId=29058&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
int maxProfit_v2(std::vector<int> &prices);

int maxProfit_v3(std::vector<int> &prices);

// https://www.nowcoder.com/practice/fdbd05d647084fcf9be78444e231998b
void populating_next_right_pointers_in_each_node(TreeLinkNode *root);

// https://www.nowcoder.com/practice/508378c0823c423baa723ce448cbfd0c?tpId=46&tqId=29067&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
bool hasPathSum(TreeNode* root, int sum);

std::vector<std::vector<int>> pathSum(TreeNode *root, int sum);

std::vector<std::vector<int>>  pathSum_bfs(TreeNode *root, int sum);

void pathSum_aux(TreeNode *root, int res,  std::vector<int> v, std::vector<std::vector<int>> &results);

} // namespace search

#endif // SEARCH_ALG_