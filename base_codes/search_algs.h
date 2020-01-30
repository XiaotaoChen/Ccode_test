#ifndef SEARCH_ALG_
#define SEARCH_ALG_

#include<string>
#include<unordered_set>

namespace search {

bool is_one_diff(const std::string& str1, const std::string& str2);
// https://www.nowcoder.com/practice/bd75ae43ff7148548eb4701550df2714?tpId=46&tqId=29054&rp=2&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking
int ladderLength(std::string start, std::string end, std::unordered_set<std::string> &dict);


} // namespace search
#endif // SEARCH_ALG_