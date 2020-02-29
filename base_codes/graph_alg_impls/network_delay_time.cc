#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // INT32_MAX

#include "../graph_algs.h"

int graph::networkDelayTime(std::vector<std::vector<int>>& times, int N, int K) {
    if (N < 2) return 0;
    int distances[N+1][N+1];
    std::fill_n(distances[0], (N+1)*(N+1), INT32_MAX);
    for (int i=0; i<times.size(); i++) {
        distances[times[i][0]][times[i][1]] = times[i][2];
        // distances[times[i][1]][times[i][0]] = times[i][2];
    }
    for (int i=0; i<N+1; i++) distances[i][i] = 0;

    bool visited[N+1];
    std::fill_n(visited, N+1, false);
    int min_dist[N+1];
    for (int i=1; i<N+1; i++) {
        min_dist[i] = distances[K][i];
    }

    visited[K] = true;
    for(int i=1; i<N+1; i++) {
        
        // find min index
        int min_val = INT32_MAX;
        int min_idx = -1;
        for (int j=1; j<N+1; j++) {
            if (visited[j] ==  false && min_val > min_dist[j]) {
                min_val = min_dist[j];
                min_idx = j;
            }
        }
        if (min_idx == -1) break;
        visited[min_idx] = true;
        //update min dist
        for (int j=1; j<N+1; j++) {
            if (visited[j] == false && distances[min_idx][j] != INT32_MAX) {
                min_dist[j] = std::min(min_dist[j], min_dist[min_idx] + distances[min_idx][j]);
            }
        }
    }
    int result = INT32_MIN;
    for (int i=1; i<N+1; i++) result = std::max(result, min_dist[i]);
    return result == INT32_MAX ? -1:result;
}