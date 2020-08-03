#include <vector>
#include <string>
#include "../thot_50.h"

namespace thot_50 {

void legal_parenthesis_dfs(std::vector<std::string>& combinations, std::string curr, int left, int right) {
    if (left == 0 && right == 0) {
        combinations.push_back(curr);
        return;
    }
    if (left > 0 ) {
        legal_parenthesis_dfs(combinations, curr + "(", left-1, right);
    }
    if (left < right) {
        legal_parenthesis_dfs(combinations, curr+")", left, right-1);
    }
    return;
}

std::vector<std::string> legal_partness(int n) {
    std::vector<std::string> result;
    legal_parenthesis_dfs(result, "",n,n);
    return result;
}

}