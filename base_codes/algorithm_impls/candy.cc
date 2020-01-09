#include <vector>
#include "../algorithm.h"

int candy(std::vector<int> &ratings) {
    int size = ratings.size();
    int a[size];
    std::fill_n(a, size, 1);
    for (int i=1; i<size; i++) {
        if (ratings[i]>ratings[i-1]) {
            a[i] = a[i-1] + 1;
        }
        else{
            int j=i-1;
            while(j>=0 && ratings[j]>ratings[j+1] && a[j] <=a[j+1]){
                a[j] = a[j+1] +1;
                j--;
            }
        }
    }
    int result=0;
    for(int i=0; i< size; i++) result+=a[i];
    return result;
}