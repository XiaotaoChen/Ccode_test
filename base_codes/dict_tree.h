#ifndef DICT_TREE_ALG
#define DICT_TREE_ALG

#include <vector>
#include <string>
#include <unordered_set>

#include "design_algs.h"
#include "data_structs/base_struct.h"

namespace dict_tree_alg
{

// https://leetcode-cn.com/problems/word-search-ii/
std::vector<std::string> findWords_v2(std::vector<std::vector<char>>& board, std::vector<std::string>& words);
void dfs_findwords_v2(std::unordered_set<std::string>& combinations, std::string curr, 
                   TrieNode* trie, std::vector<std::vector<char>>& board, 
                   std::vector<std::vector<bool>>& visited, int x, int y);

void insert_to_trienode(TrieNode* trie, std::string word);

} // namespace dict_tree_alg


#endif