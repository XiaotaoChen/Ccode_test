#include <string>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int power10(int n) {
    int result = 1;
    while(n-->0) {
        result *= 10;
    }
    return result;
}

int one_counts_dfs(std::string& str, int idx) {
    if (str.length()== idx) return 0;
    if (idx == str.length() - 1 && str[idx]=='0') return 0;
    if (idx == str.length() - 1 && str[idx] >'0') return 1;

    int len = str.length() - idx;
    // 21345 split into 0->1345,  1346->21345
    int part1 = 0;
    int firstDigit = str[idx] - '0';
    if (firstDigit > 1) {
        part1 = power10(len-1);
    }
    // 1346->21345　第五位数１的个数，　即10000->19999的个数: 10000
    else if (firstDigit == 1) {
        part1 = std::stoi(str.substr(idx+1, len-1)) + 1;
    }
    // 1346->21345中，除第五位外,　１的个数
    int part2 = firstDigit * (len-1) * power10(len-2);
    int part3 = one_counts_dfs(str, idx+1);
    return part1 + part2 + part3;
}

int one_counts(int n) {
    if (n==0) return 0;
    if (n < 10) return 1;
    std::string str = std::to_string(n);
    int result = one_counts_dfs(str, 0);
    return result;
}



} // namespace sword_finger_offer
