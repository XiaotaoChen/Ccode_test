#ifndef DYNAMIC_PROGRAMMING_ALG_
#define DYNAMIC_PROGRAMMING_ALG_

#include<string>
#include<unordered_set>

namespace dp {
    int minimumTotal(std::vector<std::vector<int> > &triangle);
    std::vector<int> getRow(int rowIndex);
    std::vector<std::vector<int> > generate(int numRows);

} // namespace dp

#endif // DYNAMIC_PROGRAMMING_ALG_