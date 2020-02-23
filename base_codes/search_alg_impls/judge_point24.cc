#include<cstdio>
#include<vector>

#include "../search_algs.h"

double search::calculate(double a , double b, char type) {
    double result = 0;
    switch (type)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        if (b <1e-10 && b > -1e-10) result = -1;
        else result = a /b;
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

bool search::judgePoint24(std::vector<int>& nums) {
    char op_types[4] = {'+', '-', '*', '/'};
    
    for (int i1=0; i1<4; i1++) {
        for (int i2=0; i2<4; i2++) {
            if (i1 == i2) continue;
            for(int i3=0; i3<4; i3++) {
                if (i3==i1||i3==i2) continue;
                int i4 = 6 -i1 -i2 -i3;

                for (int oi1=0; oi1<4; oi1++) {
                    for (int oi2 = 0; oi2<4; oi2++) {
                        for (int oi3=0; oi3<4; oi3++) {
                            double result = 0;
                            double result2 = 0;
                            // (i1 +i2) + (i3 +i4)
                            result = calculate(nums[i1], nums[i2], op_types[oi1]);
                            result2 = calculate(nums[i3], nums[i4], op_types[oi2]);
                            result = calculate(result, result2, op_types[oi3]);
                            if (result - 24 >-1e-10 && result -24 < 1e-10) return true;
                            // ((i1+i2) + i3) + i4
                            result = calculate(nums[i1], nums[i2], op_types[oi1]);
                            result2 = calculate(result, nums[i3], op_types[oi2]);
                            result = calculate(result2, nums[i4], op_types[oi3]);
                            if (result - 24 >-1e-10 && result -24 < 1e-10) return true;
                            // (i1 + (i2 +i3)) + i4
                            result = calculate(nums[i2], nums[i3], op_types[oi1]);
                            result2 = calculate(nums[i1], result, op_types[oi2]);
                            result = calculate(result2, nums[i4], op_types[oi3]);
                            if (result - 24 >-1e-10 && result -24 < 1e-10) return true;
                            // i1 + ((i2 + i3) + i4)
                            result = calculate(nums[i2], nums[i3], op_types[oi1]);
                            result2 = calculate(result, nums[i4], op_types[oi2]);
                            result = calculate(nums[i1], result2, op_types[oi3]);
                            if (result - 24 >-1e-10 && result -24 < 1e-10) return true;
                            // i1 + (i2 + (i3 +i4))
                            result = calculate(nums[i3], nums[i4], op_types[oi1]);
                            result2 = calculate(nums[i2], result, op_types[oi2]);
                            result = calculate(nums[i1], result2, op_types[oi3]);
                            if (result - 24 >-1e-10 && result -24 < 1e-10) return true;
                        }
                    }
                }

            }
        }
    }
    return false;
}