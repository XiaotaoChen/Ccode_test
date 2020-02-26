#include<vector>

#include "../greedy_algs.h"

int greedy::canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    int start = gas.size() -1;
    int end = -1;
    int res = 0;
    int curr = start;
    while(end < start) {
        res += gas[curr] - cost[curr];
        if (res >=0) {
            end++;
            curr = end;
        }
        else {
            start--;
            curr = start;
        }
    }
    if (res >=0) return start;
    return -1;
}