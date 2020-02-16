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
} // namespace dp

#endif // DYNAMIC_PROGRAMMING_ALG_