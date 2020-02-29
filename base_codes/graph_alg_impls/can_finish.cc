#include <vector>
#include <set>
#include <queue>

#include "../graph_algs.h"

std::vector<std::vector<int>> graph::create_adajct(int num, std::vector<std::vector<int>> & edges) {
    std::vector<std::vector<int>> result(num, std::vector<int>());
    for (int i=0; i<edges.size(); i++) {
        result[edges[i][1]].push_back(edges[i][0]);
    }
    return result;
}


bool graph::canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    if (numCourses < 2) return true;
    // std::vector<std::vector<int>> result = create_adajct(numCourses, prerequisites);
    std::vector<std::vector<int>> result(numCourses, std::vector<int>());
    std::vector<int> in_degrees(numCourses, 0);
    for (int i=0; i<prerequisites.size(); i++) {
        result[prerequisites[i][1]].push_back(prerequisites[i][0]);
        in_degrees[prerequisites[i][0]]++;
    }
    std::set<int> visited;
    std::queue<int> q;    
    for (int i=0; i<numCourses; i++) {
        if (in_degrees[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int curr = q.front(); q.pop();
        visited.insert(curr);
        for (int i=0; i<result[curr].size(); i++) {
            if (--in_degrees[result[curr][i]] == 0) {
                q.push(result[curr][i]);
            }
        }
    }
    if (visited.size() == numCourses) return true;
    return false;
}

std::vector<int> graph::findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<int> result;
    if (numCourses == 0) return result; 
    if (numCourses == 1) {
        result.push_back(0);
        return result;
    }

    std::vector<std::vector<int>> adjcent(numCourses, std::vector<int>());
    std::vector<int> in_degrees(numCourses, 0);
    for (int i=0; i<prerequisites.size(); i++) {
        adjcent[prerequisites[i][1]].push_back(prerequisites[i][0]);
        in_degrees[prerequisites[i][0]]++;
    }
    // std::set<int> visited;
    std::queue<int> q;    
    for (int i=0; i<numCourses; i++) {
        if (in_degrees[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int curr = q.front(); q.pop();
        result.push_back(curr);
        for (int i=0; i<adjcent[curr].size(); i++) {
            if (--in_degrees[adjcent[curr][i]] == 0) {
                q.push(adjcent[curr][i]);
            }
        }
    }
    if (result.size() == numCourses) return result;
    return std::vector<int>();
}