#include <vector>
#include <algorithm> // sort
#include <map>
#include <queue>

#include "../greedy_algs.h"

std::vector<int> greedy::advantageCount(std::vector<int>& A, std::vector<int>& B) {
    std::vector<int> result;
    if (A.size() == 0 || B.size() == 0) return result;

    std::vector<int> sortedA(A);
    std::vector<int> sortedB(B);
    std::map<int, std::queue<int>> match_map;
    std::vector<int> unmatch;

    std::sort(sortedA.begin(), sortedA.end());
    std::sort(sortedB.begin(), sortedB.end());
    
    int j=0;

    for (int i=0; i< sortedA.size(); i++) {
        if (sortedA[i]>sortedB[j]) {
            if (match_map.find(sortedB[j]) != match_map.end()) {
                match_map[sortedB[j++]].push(sortedA[i]);
            }
            else {
                std::queue<int> q;
                q.push(sortedA[i]);
                match_map[sortedB[j++]] = q;
            }
        }
        else {
            unmatch.push_back(sortedA[i]);
        }
    }
    for (int i=0; i<unmatch.size(); i++) {
        if (match_map.find(sortedB[j]) != match_map.end()) {
                match_map[sortedB[j++]].push(unmatch[i]);
            }
            else {
                std::queue<int> q;
                q.push(unmatch[i]);
                match_map[sortedB[j++]] = q;
            }
    }
    for (int i=0; i<sortedA.size(); i++) {
        result.push_back(match_map[B[i]].front());
        match_map[B[i]].pop();
    }
    return result;
}