#include "../algorithm.h"


int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int size = gas.size();
    for (int i=0; i<size; i++) {
        int remain=0;
        for (int j=0; j<size; j++) {
            int index = (i +j) % size;
            remain += gas[index] - cost[index];
            if (remain < 0) break;
        }
        if (remain >=0) return i;
    }
    return -1;
}

int canCompleteCircuit_v2(vector<int> &gas, vector<int> &cost) {
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