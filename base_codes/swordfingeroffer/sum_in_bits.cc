#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int sum_in_bits(int num1, int num2) {
    while(num2 != 0) {
        int cal = (num1 & num2) <<1; // 进位
        num1 = num1 ^ num2; // 本位结果
        num2 = cal;
    }
    return num1;
}

} // namespace sword_finger_offer
