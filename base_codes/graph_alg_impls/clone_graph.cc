#include<vector>
#include<set>
#include<queue>

#include "../graph_algs.h"

graphNode* graph::cloneGraph(graphNode* node) {
    if (node ==  nullptr) return nullptr;
    // 3 steps
    std::set<int> visited;
    std::queue<graphNode*> q;
    // 1. copy node
    graphNode* head = node;
    q.push(head);
    graphNode* curr;
    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if (visited.find(curr->val) != visited.end()) continue;
        visited.insert(curr->val);
        curr->neighbors.push_back(new graphNode(curr->val));
        
        for (int i=0; i<curr->neighbors.size()-1; i++){
            if (visited.find(curr->neighbors[i]->val) == visited.end()) q.push(curr->neighbors[i]);
        }
    }

    // 2. attach relation
    visited.clear();
    q.push(head);

    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if (visited.find(curr->val) != visited.end()) continue;
        visited.insert(curr->val);
        graphNode* copy_node = curr->neighbors.back();
        for (int i=0; i< curr->neighbors.size()-1; i++) {
            graphNode* neighbor_node = curr->neighbors[i];
            copy_node->neighbors.push_back(neighbor_node->neighbors.back());

            if (visited.find(curr->neighbors[i]->val) == visited.end()) q.push(curr->neighbors[i]);
        }
    }

    // 3. split node
    graphNode* copy_head = head->neighbors.back();
    
    visited.clear();
    q.push(head);
    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if (visited.find(curr->val) != visited.end()) continue;
        visited.insert(curr->val);
        curr->neighbors.erase(--curr->neighbors.end());

        for (int i=0; i<curr->neighbors.size(); i++){
            if (visited.find(curr->neighbors[i]->val) == visited.end()) q.push(curr->neighbors[i]);
        }
    }
    return copy_head;
}