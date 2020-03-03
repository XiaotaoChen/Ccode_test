#include <algorithm>

#include "../binary_search.h"


int binary_search::divide(int dividend, int divisor) {
    if (dividend == INT32_MIN && divisor == -1) return INT32_MAX;
    int sign = 1;
    if ((dividend >0 && divisor <0) || (dividend <0 && divisor >0)) sign = -1;

    long long dividend_l = dividend;
    long long divisor_l = divisor;

    if (dividend_l <0) dividend_l = - dividend_l;
    if (divisor_l <0) divisor_l = - divisor_l;

    long long curr_max_divisor = divisor_l;
    long long curr_res = 1;
    long long result = 0;
    while (curr_max_divisor + curr_max_divisor <= dividend_l) {
        curr_max_divisor += curr_max_divisor;
        curr_res += curr_res;
    }

    while(dividend_l >= divisor_l) {
        while(dividend_l < curr_max_divisor) {
            curr_max_divisor = curr_max_divisor >> 1;
            curr_res = curr_res >>1;
        }
        dividend_l -= curr_max_divisor;
        result += curr_res;
    }
    if (sign==1) return result;
    return -result;
}