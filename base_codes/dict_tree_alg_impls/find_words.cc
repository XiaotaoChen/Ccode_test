#include <vector>
#include <string>
#include <unordered_set>

#include "../data_structs/base_struct.h"
#include "../dict_tree.h"

namespace dict_tree_alg {

std::vector<std::string> findWords_v2(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    std::vector<std::string> result;
    if (board.size()==0||words.size()==0) return result;
    int row = board.size();
    int col = board[0].size();
    TrieNode* root = new TrieNode();
    for (int i=0; i<words.size(); i++) {
        insert_to_trienode(root, words[i]);
    }
    std::unordered_set<std::string> set;
    std::vector<std::vector<bool>> visitied(row, std::vector<bool>(col, false));
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            visitied[i][j] = true;
            dfs_findwords_v2(set, "", root, board, visitied, i, j);
            visitied[i][j] = false;
        }
    }
    for (std::unordered_set<std::string>::iterator iter=set.begin(); iter!=set.end(); iter++) {
        result.push_back(*iter);
    }
    return result;
}

void dfs_findwords_v2(std::unordered_set<std::string>& combinations, std::string curr, 
                   TrieNode* trie, std::vector<std::vector<char>>& board, 
                   std::vector<std::vector<bool>>& visited, int x, int y) {
    if (trie->next[board[x][y]-'a']==nullptr) return;
    curr += board[x][y];
    if (trie->next[board[x][y]-'a']->isEnd && combinations.find(curr)==combinations.end()) combinations.insert(curr);
    static int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    for (int i=0; i<4; i++) {
        int curr_x = x + directions[i][0];
        int curr_y = y + directions[i][1];
        if (curr_x>=0 && curr_x<board.size() && curr_y>=0 && curr_y<board[curr_x].size() && visited[curr_x][curr_y]==false) {
            visited[curr_x][curr_y] = true;
            dfs_findwords_v2(combinations, curr, trie->next[board[x][y]-'a'], board, visited, curr_x, curr_y);
            visited[curr_x][curr_y] = false;
        }
    }
    return;
}

void insert_to_trienode(TrieNode* trie, std::string word) {
    TrieNode* curr = trie;
    for (int i=0; i<word.length(); i++) {
        if (curr->next[word[i]-'a']==nullptr) {
            curr->next[word[i]-'a'] = new TrieNode();
        }
        curr = curr->next[word[i]-'a'];
    }
    curr->isEnd = true;
}

}