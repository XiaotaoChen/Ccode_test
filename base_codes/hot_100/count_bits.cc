#include <vector>
#include "../hot_100.h"

namespace hot_100
{

std::vector<int> countBits(int num) {
    std::vector<int> result(num+1, 0);
    for (int i=1;i<=num; i++) {
        if (i%2==1) result[i] += result[i-1] +1;
        else result[i] = result[i>>1];
    }
    return result;
}

} // namespace hot_100
