#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int finalNumber(int n, int m) {
    if (n==1) return 0;
    bool flags[n];
    std::fill_n(flags, n, false);

    int curr = 0;
    for (int i=0; i<n; i++) {
        int cnt = 0;
        int pre = 0;
        while(cnt <m) {
            if (!flags[curr]) {
                cnt++;
            }
            pre = curr;
            curr = (curr+1) % n;
        }
        if (i == n-1) return pre;
        flags[pre] = true;
    }

    return -1;
}

int finalNumber_v2(int n, int m) {
    if (n==1) return 0;
    return (finalNumber_v2(n-1, m) + m)%n;
}

} // namespace sword_finger_offer
