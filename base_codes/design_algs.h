#ifndef DESIGN_ALG_
#define DESIGN_ALG_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <string>
#include <stack>

#include "data_structs/base_struct.h"

namespace design_alg
{

class LRUCache {
public:
    LRUCache(int capacity);
    
    int get(int key);
    void put(int key, int value);

private:
    int cap;
    // vector是按照指数幂扩展空间的，即申请的空间为１, 2, 4, 8...当push数据超过该容量时，其会重新申请一块新区域，把原始空间内容复杂过去，
    // map中保留这原来空间的iterator，当vector申请新空间时会导致map中记录的iterator不对．应该使用list,即双向链表
    std::vector<std::pair<int, int>> cache;
    std::unordered_map<int, std::vector<std::pair<int, int>>::iterator> map;
};

class LRUCache_v2 {
private:
    int cap;
    // 双链表：装着 (key, value) 元组
    std::list<std::pair<int, int>> cache;
    // 哈希表：key 映射到 (key, value) 在 cache 中的位置
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;
public:
    LRUCache_v2(int capacity);
    
    int get(int key);
    
    void put(int key, int value);
};

class LRUCache_v3 {
public:
    LRUCache_v3(int capacity);
    ~LRUCache_v3();
    int get(int key);
    void put(int key, int value);

private:
    int cap;
    DoubleListNodeLRU *head, *tail;
    std::unordered_map<int, DoubleListNodeLRU*> map;

};

class MyStack {
public:
    MyStack();
    void push(int x);
    int pop();
    int top();
    bool empty();

private:
    std::queue<int> qu;

};

class MyQueue {
public:
   MyQueue();
   void push(int x);
   int pop();
   int front();
   bool empty();

private:
    std::stack<int> s1;
    std::stack<int> s2;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie();
    /** Inserts a word into the trie. */
    void insert(std::string word);
    /** Returns if the word is in the trie. */
    bool search(std::string word);
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix);
    Trie* get_trie();
    bool is_end();
    Trie** get_tries();
    /** match word in trie */
    bool word_dictionary_search(std::string word);
private:
    Trie* tries[26];
    bool isEnd;
};

} // namespace design_alg

#endif