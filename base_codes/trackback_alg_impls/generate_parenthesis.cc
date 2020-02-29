#include <vector>
#include <string>

#include "../trace_back_algs.h"

void track_back::track_back_generate_parenthesis(std::vector<std::string>& combinations, std::string curr, int left_count, int right_count, int n) {
    if (left_count>n || right_count >n) return ;
    if (left_count == n && right_count == n) {
        combinations.push_back(curr);
        return;
    }
    if (left_count >= right_count) {
        track_back_generate_parenthesis(combinations, curr + '(', left_count+1, right_count, n);
        track_back_generate_parenthesis(combinations, curr + ')', left_count, right_count+1, n);
    }
}

std::vector<std::string> track_back::generateParenthesis(int n) {
    std::vector<std::string> result;
    track_back_generate_parenthesis(result, "", 0, 0, n);
    return result;
}