#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>

#include "../bfs_algs.h"

bool bfs::is_one_diff(std::string str1, std::string str2) {
    if (str1.length() != str2.length()) return false;
    int diff_count = 0;
    for (int i=0; i<str1.size(); i++) {
        if (str1[i] != str2[i]) diff_count++;
    }
    if (diff_count==1) return true;
    return false;
}

int bfs::ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    if (beginWord == endWord) return 1;
    bool visited[wordList.size()];
    std::fill_n(visited, wordList.size(), false);
    bool is_in = false;
    for (int i=0; i<wordList.size(); i++) {
        if (wordList[i] == beginWord) visited[i] = true;
        if (wordList[i] == endWord) is_in = true;
    }
    if (!is_in) return 0;

    std::queue<std::string> q;
    q.push(beginWord);
    int step = 0;
    while(!q.empty()) {
        std::vector<std::string> curr_level;
        while(!q.empty()) {
            curr_level.push_back(q.front());
            q.pop();
        }
        step++;
        for (int j=0; j<curr_level.size(); j++){
            std::string curr = curr_level[j];
            if (curr == endWord) return step;
            for (int i=0; i<wordList.size(); i++) {
                if (visited[i]==false && is_one_diff(curr, wordList[i])) {
                    q.push(wordList[i]);
                    visited[i] = true;
                }
        }
        }
    }
    return 0;
}

void bfs::dfs_find_ladders(std::vector<std::vector<std::string>>& combinations, std::vector<std::string> curr, std::vector<bool>& visited, \
                           std::vector<std::string>& wordList, std::string endword) {
    if (curr.size()==0) return;
    std::string last_word = curr[curr.size()-1];
    if (last_word == endword) {
        if (combinations.size() == 0) combinations.push_back(curr);
        else {
            if (combinations[0].size() > curr.size()) {
                combinations.clear();
                combinations.push_back(curr);
            }
            else if (combinations[0].size() == curr.size()) {
                combinations.push_back(curr);
            }
        }
    }
    if (combinations.size()>0 && curr.size() >= combinations[0].size()) return;

    for (int i=0; i<wordList.size(); i++) {
        if (visited[i]==false && is_one_diff(last_word, wordList[i])) {
            visited[i] = true;
            curr.push_back(wordList[i]);
            dfs_find_ladders(combinations, curr, visited, wordList, endword);
            visited[i] = false;
            curr.erase(--curr.end());
        }
    }
}


std::vector<std::vector<std::string>> bfs::findLadders(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> curr;
    curr.push_back(beginWord);
    if (beginWord == endWord) {
        result.push_back(curr);
        return result;
    }

    std::vector<bool> visited(wordList.size(), false);
    bool is_in = false;
    for (int i=0; i<wordList.size(); i++) {
        if (wordList[i] == beginWord) visited[i] = true;
        if (wordList[i] == endWord) is_in = true;
    }
    if (!is_in) return result;

    dfs_find_ladders(result, curr, visited, wordList, endWord);
    return result;
}

std::vector<std::vector<std::string>> bfs::findLadders_v2(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> curr;
    curr.push_back(beginWord);
    if (beginWord == endWord) {
        result.push_back(curr);
        return result;
    }

    std::vector<bool> visited(wordList.size(), false);
    bool is_in = false;
    for (int i=0; i<wordList.size(); i++) {
        if (wordList[i] == beginWord) visited[i] = true;
        if (wordList[i] == endWord) is_in = true;
    }
    if (!is_in) return result;

    std::queue<std::vector<std::string>> q;
    q.push(curr);
    bool exist = false;
    while(!q.empty()) {
        std::vector<std::vector<std::string>> curr_layer;
        while(!q.empty()) {
            curr = q.front(); q.pop();
            curr_layer.push_back(curr);
        }
        std::vector<int> layer_visited;
        for (int i=0; i<curr_layer.size(); i++) {
            curr = curr_layer[i];
            std::string last_word = curr[curr.size()-1];
            if (last_word == endWord) {
                result.push_back(curr);
                exist = true;
            }
            else {
                for (int j=0; j<wordList.size(); j++) {
                    if (visited[j]==false && is_one_diff(last_word, wordList[j])) {
                        std::vector<std::string> tmp_cpy(curr);
                        tmp_cpy.push_back(wordList[j]);
                        q.push(tmp_cpy);
                        layer_visited.push_back(j);
                    }
                }
            }
        }
        for (int i=0; i<layer_visited.size(); i++) visited[layer_visited[i]] = true;
        if (exist) break;
    }
    return result;
}

void bfs::dfs_generate(std::vector<std::vector<std::string>>& combinations, std::string beginWord, std::string endWord, \
                  std::map<std::string, std::vector<std::string>>& path_map, std::vector<std::string> curr) {
    if (beginWord == endWord) {
        std::reverse(curr.begin(), curr.end());
        combinations.push_back(curr);
        std::reverse(curr.begin(), curr.end());
        return;
    }
    std::vector<std::string> tmp = path_map[beginWord];
    for (int i=0; i<tmp.size(); i++) {
        curr.push_back(tmp[i]);
        dfs_generate(combinations, tmp[i], endWord, path_map, curr);
        curr.erase(--curr.end());
    }
}

std::vector<std::vector<std::string>> bfs::findLadders_v3(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::vector<std::vector<std::string>> result;
    if (beginWord == endWord) {
        std::vector<std::string> curr;
        curr.push_back(beginWord);
        result.push_back(curr);
        return result;
    }

    std::vector<bool> visited(wordList.size(), false);
    bool is_in = false;
    for (int i=0; i<wordList.size(); i++) {
        if (wordList[i] == beginWord) visited[i] = true;
        if (wordList[i] == endWord) is_in = true;
    }
    if (!is_in) return result;

    std::queue<std::string> q;
    std::map<std::string, std::vector<std::string>> path_map;
    q.push(beginWord);
    
    while(!q.empty()) {
        std::vector<std::string> curr_layer;
        while(!q.empty()){
            curr_layer.push_back(q.front());
            q.pop();
        }
        bool exist = false;
        for (int j=0; j<curr_layer.size(); j++) {
            if (curr_layer[j]==endWord) {
                exist = true;
                break;
            }
        }
        if (exist) break;
        std::vector<int> curr_visit;
        for (int i=0; i<curr_layer.size(); i++) {
            for (int j=0; j<wordList.size(); j++) {
                if (visited[j]==false && is_one_diff(curr_layer[i], wordList[j])) {
                    path_map[wordList[j]].push_back(curr_layer[i]);
                    curr_visit.push_back(j);
                }
            }
        }
        for (int i=0; i<curr_visit.size(); i++) {
            if (visited[curr_visit[i]]) continue;
            visited[curr_visit[i]] = true;
            q.push(wordList[curr_visit[i]]);

        }
    }

    std::vector<std::string> curr;
    curr.push_back(endWord);
    dfs_generate(result, endWord, beginWord, path_map, curr);
    return result;
}
