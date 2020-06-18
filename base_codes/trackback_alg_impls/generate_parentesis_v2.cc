#include <string>
#include <vector>
#include "../trace_back_algs.h"

namespace track_back
{

void generate_dfs(std::vector<std::string>& combinations, std::string curr, int left_res, int right_res) {
    if (left_res == 0 && right_res == 0) {
        combinations.push_back(curr);
        return;
    }
    if (left_res > 0) {
        generate_dfs(combinations, curr + '(', left_res-1, right_res);
    }
    if (right_res > 0 && left_res < right_res) {
        generate_dfs(combinations, curr+')', left_res, right_res-1);
    }
}

std::vector<std::string> generateParenthesis_v2(int n) {
    std::vector<std::string> result;
    generate_dfs(result, "", n, n);
    return result;
}

} // namespace track_back
