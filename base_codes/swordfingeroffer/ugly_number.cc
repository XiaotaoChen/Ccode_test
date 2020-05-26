#include <algorithm>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int ugly_number(int index) {
    if (index<=0) return -1;
    if (index ==1) return 1;
    int ugly_numbers[index];
    ugly_numbers[0] = 1;
    int* mult2, *mult3, *mult5;
    mult2 = ugly_numbers;
    mult3 = ugly_numbers;
    mult5 = ugly_numbers;
    int curr = 1;
    while(curr < index) {
        int num=  std::min(std::min((*mult2)*2, (*mult3)*3), (*mult5)*5);
        ugly_numbers[curr] = num;
        while((*mult2*2) <= num) mult2++;
        while((*mult3*3) <= num) mult3++;
        while((*mult5*5) <= num) mult5++;
        curr++;
    }
    return ugly_numbers[index-1];
}

} // namespace sword_finger_offer
