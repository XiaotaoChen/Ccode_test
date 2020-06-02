#include <vector>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

std::pair<int, int> appearOnce(std::vector<int>& arr) {
    // get the first 1 of bits
    int flag = 0;
    for (int& num : arr) {
        flag ^= num;
    }
    flag = flag & (1 - flag);
    
    // split arr into two arr
    std::vector<int> arr1, arr2;
    for (int num : arr) {
        if ((flag & num) == 0) {
            arr1.push_back(num);
        }
        else {
            arr2.push_back(num);
        }
    }

    std::pair<int, int> result(0,0);
    for (int& num:arr1){
        result.first ^= num;
    }
    for (int & num:arr2) {
        result.second ^= num;
    }

    return result;
}

int appearOnce_of_three(std::vector<int>& arr) {
    if (arr.size()==1) return arr[0];
    int bits[32];
    std::fill_n(bits, 32, 0);
    for (int& num : arr) {
        int bitmask = 1;
        for (int i=0; i< 32; i++) {
            if ((num & bitmask) != 0) bits[i]++;
            bitmask = bitmask<<1;
        }
    }
    int result = 0;
    for (int i =0; i<32; i++) {
        if (bits[i]%3!=0) {
            result += 1<<i;
        }
    }
    return result;
}

int appearOnce_of_three_v2(std::vector<int>& arr) {
    if (arr.size()==1) return arr[0];
    int one, two, three;
    one = two = three = 0;
    for (int& num: arr) {
        two |= (one & num); // 出现两次的比特位
        one = one ^ num; // 出现一次的比特位
        three = two & one; // 出现三次的比特位
        two = two & (~three); //若出现三次，则将two, one对应的比特位置０
        one = one & (~three);
    }
    return one;
}

} // namespace sword_finger_offer
