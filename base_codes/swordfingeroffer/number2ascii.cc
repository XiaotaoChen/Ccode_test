#include <string>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int number2ascii(int num) {
    if (num <0) return -1;
    std::string str_num = std::to_string(num);
    int len = str_num.length();
    if (len==1) return 1;
    int dp[len+1];
    std::fill_n(dp, len+1, 0);
    dp[0]=1;
    dp[1] = 1;
    for (int i=2; i<=len; i++) {
        if (std::stoi(str_num.substr(i-2,2)) <= 25){
            dp[i]= dp[i-1] + dp[i-2];
        }
        else {
            dp[i] = dp[i-1];
        }
    }
    return dp[len];
}

} // namespace sword_finger_offer
