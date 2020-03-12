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

int greedy::canCompleteCircuit_v2(std::vector<int> &gas, std::vector<int> &cost) {
    int end = 0;
    int start = gas.size() -1;
    int remain = gas[start] - cost[start];
    while(start > end) {
        if (remain>=0){
            remain += gas[end] - cost[end];
            end ++; // end++ must behind of remain
        }
        else{
            start --; // start-- must ahead of remain
            remain += gas[start] - cost[start];
        }
    }
    if (remain>=0) return start;
    return -1;
}