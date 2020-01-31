#include<vector>
#include<queue>
#include<map>
#include<algorithm> // std::reverse
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
        while(!qu.empty()){
            curr_layer.push_back(qu.front());
            qu.pop();
        }
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

std::vector<std::vector<std::string> > search::findLadders(std::string start, std::string end, std::unordered_set<std::string> &dict) {
    std::vector<std::string> dict_vec;
    dict_vec.insert(dict_vec.end(), dict.begin(), dict.end());
    std::queue<std::vector<std::string> > qu;
    std::vector<std::string> start_str;
    start_str.push_back(start);
    qu.push(start_str);
    std::vector<bool> visited(dict.size());
    bool exist = false;
    std::vector<std::vector<std::string> > result;
    while(!qu.empty()) {
        std::vector<std::vector<std::string> > curr_layer;
        while(!qu.empty()){
            curr_layer.push_back(qu.front());
            qu.pop();
        }
        for (int curr_idx=0; curr_idx<curr_layer.size(); curr_idx++){
            std::vector<std::string> curr_vec = curr_layer[curr_idx];
            std::string curr = curr_vec[curr_vec.size() - 1];
            if (is_one_diff(curr, end)) {
                curr_vec.push_back(end);
                result.push_back(curr_vec);
                exist = true;
            }
            for(int i=0; i<dict_vec.size(); i++) {
                if(visited[i] == false && is_one_diff(curr, dict_vec[i])) {
                    std::vector<std::string> tmp_cpy(curr_vec); 
                    tmp_cpy.push_back(dict_vec[i]);
                    qu.push(tmp_cpy);
                    visited[i] = true;
                }
            }
        }
        if(exist) break;
    }
    // if (exist) return result;
    return result;  
}

void search::generate(std::map<std::string, std::vector<std::string> > &path_map, 
                                                        std::string& start, 
                                                        std::string& end,
                                                        std::vector<std::string>& tmp_path,
                                                        std::vector<std::vector<std::string> >& result) {
    if (start == end) {
        std::reverse(tmp_path.begin(), tmp_path.end());
        result.push_back(tmp_path);
        std::reverse(tmp_path.begin(), tmp_path.end());
        return;
    }
    std::vector<std::string> tmp = path_map[start];
    for(int i=0; i<tmp.size(); i++) {
        tmp_path.push_back(tmp[i]);
        generate(path_map, tmp[i], end, tmp_path, result);
        tmp_path.pop_back();
    }
}

std::vector<std::vector<std::string> > search::findLadders_V2(std::string start, std::string end, std::unordered_set<std::string> &dict) {
    std::vector<std::string> dict_vec;
    dict_vec.insert(dict_vec.end(), dict.begin(), dict.end());
    std::queue<std::string> qu;
    qu.push(start);
    std::vector<bool> visited(dict.size());
    bool exist = false;
    std::map<std::string, std::vector<std::string> > path_map;
    while(!qu.empty()) {
        std::vector<std::string> curr_layer;
        while(!qu.empty()){
            curr_layer.push_back(qu.front());
            qu.pop();
        }
        for (int curr_idx=0; curr_idx<curr_layer.size(); curr_idx++){
            std::string curr = curr_layer[curr_idx];
            if (is_one_diff(curr, end)) {
                // if (path_map.find(end) == path_map.end()) {
                //         std::vector<std::string> tmp;
                //         tmp.push_back(curr);
                //         path_map[end] = tmp;
                // }
                // else {
                //     path_map[end].push_back(curr);
                // }
                path_map[end].push_back(curr);
                exist = true;
            }
            for(int i=0; i<dict_vec.size(); i++) {
                if(visited[i] == false && is_one_diff(curr, dict_vec[i])) {
                    qu.push(dict_vec[i]);
                    visited[i] = true;
                    // if (path_map.find(dict_vec[i]) == path_map.end()) {
                    //     std::vector<std::string> tmp;
                    //     tmp.push_back(curr);
                    //     path_map[dict_vec[i]] = tmp;
                    // }
                    // else {
                    //     path_map[dict_vec[i]].push_back(curr);
                    // }
                    path_map[dict_vec[i]].push_back(curr);
                }
            }
        }
        if(exist) break;
    }
    std::vector<std::vector<std::string> > result;
    std::vector<std::string> tmp_path = {end};
    generate(path_map, end, start, tmp_path, result);
    return result;
}