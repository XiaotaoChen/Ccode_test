#include <vector>
#include <algorithm>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int giftmaxval(std::vector<std::vector<int>>& gifts) {
    if (gifts.size() == 0 || gifts[0].size() == 0)  return 0;
    int row = gifts.size();
    int col = gifts[0].size();
    int dp[col+1];
    std::fill_n(dp, col+1, 0);
    for (int i=0; i<row; i++) {
        for (int j=0; j< col; j++) {
            dp[j+1] = std::max(dp[j+1], dp[j]) + gifts[i][j];
        }
    }
    return dp[col];
}

} // namespace sword_finger_offer
