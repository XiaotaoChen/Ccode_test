//#include <math.h>
#include <cmath>
#include <stdio.h>

int main() {
    int data = 4;
    //float result = pow(2, data);
    float result = std::pow(2, data);
    printf("pow(2, %d):%.2f\n", data, result);
    return 0;
}
