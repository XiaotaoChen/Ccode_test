#include <list>
#include <unordered_map>
#include "../algorithms.h"

namespace algorithms
{

int LRUCache::get(int key) {
    if (mp.find(key) == mp.end()) return -1;
    int val = (*mp[key]).second;
    list.erase(mp[key]);
    list.push_front(std::make_pair(key, val));
    mp[key] = list.begin();
    return val;
}

void LRUCache::put(int key, int value) {
    if (mp.find(key) != mp.end()) {
        mp.erase(key);
        list.push_front(std::make_pair(key, value));
        mp[key] = list.begin();
    }
    else if (list.size() < capacity) {
        list.push_front(std::make_pair(key, value));
        mp[key] = list.begin();
    }
    else {
        int to_delete = list.back().first;
        mp.erase(to_delete);
        list.pop_back();
        list.push_front(std::make_pair(key, value));
        mp[key] = list.begin();
    }
}

} // namespace algorithms
