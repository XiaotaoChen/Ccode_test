#include <vector>
#include <queue>
#include <set>

#include "../graph_algs.h"

std::vector<int> graph::findMinHeightTrees(int n, std::vector<std::vector<int>>& edges) {
    std::vector<int> result;
    if (n==0) return result;
    if (n==1) {
        result.push_back(0);
        return result;
    }
    if (n==2) {
        result.push_back(0);
        result.push_back(1);
        return result;
    }

    std::vector<std::vector<int>> adjcent(n, std::vector<int>());
    std::vector<int> degrees(n, 0);
    for (int i=0; i<edges.size(); i++) {
        adjcent[edges[i][0]].push_back(edges[i][1]);
        adjcent[edges[i][1]].push_back(edges[i][0]);
        degrees[edges[i][0]]++;
        degrees[edges[i][1]]++;
    }

    std::queue<int> q;
    for (int i=0; i<n; i++) {
        if (degrees[i] == 1) q.push(i);
    }

    std::set<int> visited;
    int res_num = n;
    while(res_num>2 && !q.empty()) {
        std::vector<int> tmp_vec;
        while(!q.empty()) {
            tmp_vec.push_back(q.front());
            visited.insert(q.front());
            res_num--;
            q.pop();
        }
        for (int i=0; i<tmp_vec.size(); i++) {
            for (int j=0; j<adjcent[tmp_vec[i]].size(); j++) {
                degrees[tmp_vec[i]]--;
                degrees[adjcent[tmp_vec[i]][j]]--;
            }
        }

        for (int i=0; i<n; i++) {
        if (degrees[i] == 1) q.push(i);
        }
    }
    for (int i=0; i<n; i++) {
        if (visited.find(i)==visited.end()) result.push_back(i);
    }
    return result;
}