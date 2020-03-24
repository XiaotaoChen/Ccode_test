

namespace minimization_alg
{

bool canWinNim(int n) {
    if (n < 4) return true;
    bool dp[4] = {false, true, true, true};
    for (int i=4; i<=n;i++) {
        dp[i%4] = !(dp[(i-3)%4]&dp[(i-2)%4]&dp[(i-1)%4]);
    }
    return dp[n%4];
}

} // namespace minmization_alg