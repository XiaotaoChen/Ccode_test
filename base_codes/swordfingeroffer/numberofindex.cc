#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int pow(int base, int n) {
    int result = 1;
    while(n-- > 0) {
        result *= base;
    }
    return result;
}

int countofdigit(int n) {
    return 9 * pow(10, n-1) * n;
}

int digitofindex(int num, int lastindex) {
    while(lastindex-- >0) {
        num /= 10;
    }
    return num % 10;
}

int numberofindex(int index) {
    if (index < 10) return index;
    int digit = 1;
    while(index  > countofdigit(digit)) {
        index -= countofdigit(digit);
        digit++;
    }

    int begin_num = pow(10, digit-1);
    int num = begin_num + (index-1) / digit;
    int lastindex = digit - (index-1) % digit - 1;
    int result = digitofindex(num, lastindex);
    return result;

}

} // namespace sword_finger_offer
