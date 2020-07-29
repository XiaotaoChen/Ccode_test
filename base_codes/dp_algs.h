#ifndef DYNAMIC_PROGRAMMING_ALG_
#define DYNAMIC_PROGRAMMING_ALG_

#include<string>
#include<unordered_set>
#include<vector>

namespace dp {
    int minimumTotal(std::vector<std::vector<int> > &triangle);
    std::vector<int> getRow(int rowIndex);
    std::vector<std::vector<int> > generate(int numRows);

    //https://www.nowcoder.com/practice/ed2923e49d3d495f8321aa46ade9f873?tpId=46&tqId=29065&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
    int min_distance_of_str(std::string S, std::string T);

// https://leetcode-cn.com/problems/longest-palindromic-substring/
std::string longestPalindrome_v2(std::string s);
std::string longestPalindrome_v3(std::string s);
std::string longestPalindrome_v4(std::string s);
std::string longestPalindrome_v5(std::string s);

// https://leetcode-cn.com/problems/regular-expression-matching/
bool regular_match(std::string s, std::string p);
bool isLegal(char normal, char match);
bool regular_match_v2(std::string& s, std::string& p);
bool regular_match_v3(std::string& s, std::string& p);
bool regular_match_v4(std::string& s, std::string& p);

// https://leetcode-cn.com/problems/maximal-square/comments/
int maximalSquare(std::vector<std::vector<char>>& matrix);


// https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/
int mctFromLeafValues(std::vector<int>& arr);

// https://leetcode-cn.com/problems/maximum-subarray/
int maxSubArray(std::vector<int>& nums);
int maxSubArray_v2(std::vector<int>& nums);

// https://leetcode-cn.com/problems/unique-paths/
int uniquePaths(int m, int n);
int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid);

 // https://leetcode-cn.com/problems/maximal-rectangle/
 int maximalRectangle(std::vector<std::vector<char>>& matrix);
int max_rectangle(std::vector<int>& heights);

// https://leetcode-cn.com/problems/edit-distance/
int minDistance(std::string& word1, std::string& word2);
int minDistance_v2(std::string& word1, std::string& word2);
int minDistance_v3(std::string& word1, std::string& word2);

// https://leetcode-cn.com/problems/minimum-path-sum/
int minPathSum(std::vector<std::vector<int>>& grid);

// https://leetcode-cn.com/problems/unique-binary-search-trees/
int numTrees(int n);


std::vector<std::string> wordBreak(std::string s, std::unordered_set<std::string> &dict); 

// https://leetcode-cn.com/problems/word-break/
bool wordBreak_single(std::string s, std::vector<std::string>& wordDict);

int palindrome_minCut(std::string& str);

} // namespace dp

#endif // DYNAMIC_PROGRAMMING_ALG_