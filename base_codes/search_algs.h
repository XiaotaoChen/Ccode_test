#ifndef SEARCH_ALG_
#define SEARCH_ALG_

#include<string>
#include<unordered_set>
#include <unordered_map>
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
    int maxPathSum_V2(TreeNode *root);
}

int maxProfit(std::vector<int> &prices);

// https://www.nowcoder.com/practice/572903b1edbd4a33b2716f7649b4ffd4?tpId=46&tqId=29058&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
int maxProfit_v2(std::vector<int> &prices);

int maxProfit_v3(std::vector<int> &prices);

// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/
int maxProfit_v4(std::vector<int>& prices);

// https://www.nowcoder.com/practice/fdbd05d647084fcf9be78444e231998b
void populating_next_right_pointers_in_each_node(TreeLinkNode *root);

// https://www.nowcoder.com/practice/508378c0823c423baa723ce448cbfd0c?tpId=46&tqId=29067&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
bool hasPathSum(TreeNode* root, int sum);

std::vector<std::vector<int>> pathSum(TreeNode *root, int sum);

std::vector<std::vector<int>>  pathSum_bfs(TreeNode *root, int sum);

void pathSum_aux(TreeNode *root, int res,  std::vector<int> v, std::vector<std::vector<int>> &results);

// https://leetcode-cn.com/problems/add-two-numbers/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

ListNode* addTwoNumbers_v2(ListNode* l1, ListNode* l2);


// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(std::string s);

int is_include(std::string s, int left, int right, char ch);

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);

double findMedianSortedArrays_v2(std::vector<int>& nums1, std::vector<int>& nums2);

int mid_val_k(std::vector<int>& nums1, int low1, std::vector<int>& nums2, int low2, int k);

// https://leetcode-cn.com/problems/longest-palindromic-substring/
std::string longestPalindrome(std::string s);


// https://leetcode-cn.com/problems/zigzag-conversion/
std::string z_convert(std::string s, int numRows);

// https://leetcode-cn.com/problems/string-to-integer-atoi/
int myAtoi(std::string str);

std::string valid_string(std::string str);

// https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
int largestRectangleArea(std::vector<int>& heights);

// https://leetcode-cn.com/problems/container-with-most-water/
int maxArea(std::vector<int>& height);
int get_max_area(std::vector<int>& heights, std::vector<int>& idxs, int curr_idx);

int maxArea_v2(std::vector<int>& height);
int maxArea_v3(std::vector<int>& height);

// https://leetcode-cn.com/problems/integer-to-roman/
std::string intToRoman(int num);
std::string intToRoman_v2(int num);
std::string intToRoman_v3(int num);

// https://leetcode-cn.com/problems/subtree-of-another-tree/
bool isSubtree(TreeNode* s, TreeNode* t);
bool isSametree(TreeNode* s, TreeNode* t);

// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
bool canReach(TreeNode* root, TreeNode* node);
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q);

// https://leetcode-cn.com/problems/most-frequent-subtree-sum/
std::vector<int> findFrequentTreeSum(TreeNode* root);
int treeSum(TreeNode* root, std::map<int, int>& freq, int& max_freq, std::vector<int>& max_freq_sum);

// https://leetcode-cn.com/problems/simplify-path/
std::string simplifyPath(std::string path);
std::vector<std::string> splitstr(std::string path);

std::string simplifyPath_V2(std::string path);

ListNode* reverseBetween(ListNode* head, int m, int n);


// https://leetcode-cn.com/problems/24-game/
bool judgePoint24(std::vector<int>& nums);
double calculate(double a , double b, char type);

bool judgePoint24_v2(std::vector<double>& nums, char* op_types);

// https://leetcode-cn.com/problems/spiral-matrix/
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix);

std::vector<std::vector<int>> generateMatrix(int n);

void match_idx_val(std::vector<int>& vec, std::vector<int>& result, int left, int right);
void match_idx_val_v2(std::vector<int>& vec, std::vector<int>& result, int left, int right);

// https://leetcode-cn.com/problems/3sum/
std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
std::vector<std::vector<int>> threeSum_v2(std::vector<int>& nums);
std::vector<std::vector<int>> threeSum_v3(std::vector<int>& nums);

// https://leetcode-cn.com/problems/rotate-image/
void rotate(std::vector<std::vector<int>>& matrix);
void rotate_v2(std::vector<std::vector<int>>& matrix);

// https://leetcode-cn.com/problems/group-anagrams/
std::unordered_map<char, int> get_ch_map(std::string& str);
std::map<char, int> get_ch_map2(std::string& str);
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);

std::vector<std::vector<std::string>> groupAnagrams_v2(std::vector<std::string>& strs);

} // namespace search

#endif // SEARCH_ALG_