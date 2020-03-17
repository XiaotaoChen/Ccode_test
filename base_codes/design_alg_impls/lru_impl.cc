#include <vector>
#include <unordered_map>
#include <list>

#include "../design_algs.h"

namespace design_alg {

LRUCache::LRUCache(int capacity) : cap(capacity) {}

int LRUCache::get(int key) {
    if (map.find(key)== map.end()) return -1;
    std::pair<int, int> curr = *map[key];
    cache.erase(map[key]);
    cache.insert(cache.begin(), curr);
    map[key] = cache.begin();
    return curr.second;
}

void LRUCache::put(int key, int value) {
    if (map.find(key)!=map.end()) {
        std::pair<int ,int> curr = *map[key];
        cache.erase(map[key]);
        cache.insert(cache.begin(), {key, value});
        map[key] = cache.begin();
    }
    else {
        if (cache.size()==cap) {
            std::pair<int, int> last = cache.back();
            cache.pop_back();
            map.erase(last.first);
        }
        cache.insert(cache.begin(), {key, value});
        map[key] = cache.begin();
    }
}

LRUCache_v2::LRUCache_v2(int capacity) {
    this->cap = capacity; 
}

int LRUCache_v2::get(int key) {
    auto it = map.find(key);
    // 访问的 key 不存在
    if (it == map.end()) return -1;
    // key 存在，把 (k, v) 换到队头
    std::pair<int, int> kv = *map[key];
    cache.erase(map[key]);
    cache.push_front(kv);
    // 更新 (key, value) 在 cache 中的位置
    map[key] = cache.begin();
    return kv.second; // value
}

void LRUCache_v2::put(int key, int value) {

    /* 要先判断 key 是否已经存在 */ 
    auto it = map.find(key);
    if (it == map.end()) {
        /* key 不存在，判断 cache 是否已满 */ 
        if (cache.size() == cap) {
            // cache 已满，删除尾部的键值对腾位置
            // cache 和 map 中的数据都要删除
            auto lastPair = cache.back();
            int lastKey = lastPair.first;
            map.erase(lastKey);
            cache.pop_back();
        }
        // cache 没满，可以直接添加
        cache.push_front({key, value});
        map[key] = cache.begin();
    } else {
        /* key 存在，更改 value 并换到队头 */
        cache.erase(map[key]);
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
}

LRUCache_v3::LRUCache_v3(int capacity): cap(capacity) {
    head = new DoubleListNodeLRU(-1, -1);
    tail = new DoubleListNodeLRU(-1, -1);
    head->right = tail;
    tail->left = head;
}

LRUCache_v3::~LRUCache_v3() {
    delete head;
    delete tail;
}

int LRUCache_v3::get(int key) {
    if (map.find(key)==map.end()) return -1;
    DoubleListNodeLRU* curr = map[key];
    // move curr to head;
    curr->left->right = curr->right;
    curr->right->left = curr->left;

    curr->right = head->right;
    head->right->left = curr;
    curr->left = head;
    head->right = curr;
    return curr->val;
}

void LRUCache_v3::put(int key, int value) {
    if (map.find(key)==map.end()) {
        if (map.size()==cap) {
            //delete tail
            DoubleListNodeLRU* last = tail->left;
            last->left->right = last->right;
            tail->left = last->left;

            map.erase(last->key);
            delete last;
        }
        DoubleListNodeLRU* curr = new DoubleListNodeLRU(key, value);
        map[key] = curr;
        curr->right = head->right;
        head->right->left = curr;
        curr->left = head;
        head->right = curr;
    }
    else {
        // move curr to head;
        DoubleListNodeLRU* curr = map[key];
        curr->left->right = curr->right;
        curr->right->left = curr->left;

        curr->right = head->right;
        head->right->left = curr;
        curr->left = head;
        head->right = curr;
    }
}

}


