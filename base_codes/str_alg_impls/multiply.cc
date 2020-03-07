#include <string>

#include "../str_algs.h"


std::string str_alg::multiply(std::string num1, std::string num2) {
    if (num1.length()==0||num2.length()==0) return "";
    if (num1[0]=='0'||num2[0]=='0') return "0";

    int n1 = num1.length();
    int n2 = num2.length();

    int nums1[n1];
    int nums2[n2];
    int result[n1 + n2];
    std::fill_n(result, n1+n2, 0);
    for (int i=0; i<n1; i++) nums1[n1-1-i] = num1[i] - '0';
    for (int i=0; i<n2; i++) nums2[n2-1-i] = num2[i] - '0';

    for (int i=0; i<n1; i++) {
        for (int j=0; j<n2; j++) {
            int tmp = nums1[i] * nums2[j];
            result[i+j] += tmp%10;
            result[i+j+1] += tmp / 10;
        }
    }
    // process result 
    for (int i=0; i<n1+n2-1; i++) {
        result[i+1] += result[i]/10;
        result[i] %= 10;
    }

    int end = n1+n2-1;
    while (result[end]==0) end--;
    std::string str = "";
    for (int i=end; i>=0; i--) str += ('0' + result[i]);
    return str;
    
}