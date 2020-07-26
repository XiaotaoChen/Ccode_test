#include <algorithm>
#include "../thot_50.h"

namespace thot_50
{

int reverse(int x) {
    long result = 0;
    while(x!=0) {
        result = result * 10 + x%10;
        x /= 10;
    }
    if (result > INT32_MAX || result < INT32_MIN) return 0;
    return (int)result;
}

} // namespace thot_50
