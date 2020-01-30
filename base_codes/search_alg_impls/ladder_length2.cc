#include<vector>
#include<queue>
#include "../search_algs.h"

bool search::is_one_diff(const std::string& str1, const std::string& str2) {
    int len = str1.length();
    int diff = 0;
    for(int i=0; i<len; i++) {
        if (str1[i] != str2[i]) diff++;
    }
    if (diff==1) return true;
    return false;
}

// bfs
int search::ladderLength(std::string start, std::string end, std::unordered_set<std::string> &dict) {
    std::vector<std::string> dict_vec;
    dict_vec.insert(dict_vec.end(), dict.begin(), dict.end());
    std::queue<std::string> qu;
    qu.push(start);
    std::vector<bool> visited(dict.size());
    int depth = 0;
    bool exist = false;
    while(!qu.empty()) {
        std::vector<std::string> curr_layer;
        depth++;
        printf("depth:%d: ", depth);
        while(!qu.empty()){
            printf("%s ", qu.front().c_str());
            curr_layer.push_back(qu.front());
            qu.pop();
        }
        printf("\n");
        for (int curr_idx=0; curr_idx<curr_layer.size(); curr_idx++){
            std::string curr = curr_layer[curr_idx];
            if (is_one_diff(curr, end)) {
                exist = true;
                break;
            }
            for(int i=0; i<dict_vec.size(); i++) {
                if(visited[i] == false && is_one_diff(curr, dict_vec[i])) {
                    qu.push(dict_vec[i]);
                    visited[i] = true;
                }
            }
        }
        if(exist) break;
    }
    if (exist) return depth +1;
    return 0;
}