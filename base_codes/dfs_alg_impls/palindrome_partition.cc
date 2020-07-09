#include <vector>
#include <string>
#include "../dfs_algs.h"

namespace dfs
{

void palindrome_partition_dfs(std::vector<std::vector<std::string>>& combinations, std::vector<std::string>& curr_vector, std::string& str, int index) {
    if (index == str.length()) {
        combinations.push_back(curr_vector);
    }
    for (int i=index; i<str.length(); i++) {
        std::string substr = str.substr(index, i-index+1);
        if (substr == std::string(substr.rbegin(), substr.rend())) {
            curr_vector.push_back(substr);
            palindrome_partition_dfs(combinations, curr_vector, str, i+1);
            curr_vector.pop_back();
        }
    }
}

std::vector<std::vector<std::string>> palindrome_partition(std::string str) {
    std::vector<std::vector<std::string>> result;
    if (str.length()==0) return result;
    std::vector<std::string> curr;
    palindrome_partition_dfs(result, curr, str, 0);
}

} // namespace dfs
