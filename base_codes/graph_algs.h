#ifndef GRAPH_ALG_
#define GRAPH_ALG_

#include<vector>

#include "data_structs/base_struct.h"

namespace graph {

// https://leetcode-cn.com/problems/clone-graph/
graphNode* cloneGraph(graphNode* node);

// https://leetcode-cn.com/problems/course-schedule/
bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites);
std::vector<std::vector<int>> create_adajct(int num, std::vector<std::vector<int>> & edges);

// https://leetcode-cn.com/problems/course-schedule-ii/
std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites);

// https://leetcode-cn.com/problems/minimum-height-trees/
std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges);

// https://leetcode-cn.com/problems/network-delay-time/
int networkDelayTime(std::vector<std::vector<int>>& times, int N, int K);

}

#endif  // GRAPH_ALG_
