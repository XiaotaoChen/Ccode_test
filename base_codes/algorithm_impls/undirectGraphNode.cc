#include "../algorithm.h"
#include<stack>
#include<set>
#include<memory>

void print_graph(UndirectedGraphNode* node) {
    set<int> visited;
    stack<UndirectedGraphNode*> st;
    st.push(node);
    while(!st.empty()) {
        UndirectedGraphNode* curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) continue;
        printf("%d", curr->label);
        for (auto gnode: curr->neighbors) {
            printf(",%d", gnode->label);
            st.push(gnode);
        }
        printf("\n");
        visited.insert(curr->label);
    }
}

UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
    if (node == NULL) return NULL;
    set<int> visited;
    // clone each node and insert to 0
    stack<UndirectedGraphNode*> st;
    st.push(node);
    while(!st.empty()) {
        UndirectedGraphNode* curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) continue;
        UndirectedGraphNode* tmp = new UndirectedGraphNode(curr->label);
        // shared_ptr<UndirectedGraphNode> tmp = shared_ptr<UndirectedGraphNode>(new UndirectedGraphNode(curr->label));
        // copy neighbors to tmp
        for (auto gnode: curr->neighbors) st.push(gnode);
        curr->neighbors.insert(curr->neighbors.begin(), tmp);
        visited.insert(curr->label);
    }
    // update neighbors
    visited.clear();
    st.push(node);
    while(!st.empty()) {
        UndirectedGraphNode* curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) continue;
        for (vector<UndirectedGraphNode*>::iterator iter=curr->neighbors.begin() +1; iter!=curr->neighbors.end(); iter++) {
            curr->neighbors[0]->neighbors.push_back((*iter)->neighbors[0]);
            st.push(*iter);
        }
        visited.insert(curr->label);
    }
    // split 
    visited.clear();
    UndirectedGraphNode* copy_head = node->neighbors[0];
    st.push(node);
    while(!st.empty()) {
        UndirectedGraphNode* curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) curr->neighbors.erase(curr->neighbors.begin());
        visited.insert(curr->label);
    }
    return copy_head;
}

// wrong usage for share_ptr,which will free new graph_node when share_ptr is out of namespace
UndirectedGraphNode* cloneGraph_v2(UndirectedGraphNode* node) {
    if (node == NULL) return NULL;
    shared_ptr<UndirectedGraphNode> s_node = shared_ptr<UndirectedGraphNode>(node);
    set<int> visited;
    // clone each node and insert to 0
    stack<shared_ptr<UndirectedGraphNode> > st;
    st.push(s_node);
    while(!st.empty()) {
        shared_ptr<UndirectedGraphNode> curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) continue;
        shared_ptr<UndirectedGraphNode> tmp = shared_ptr<UndirectedGraphNode>(new UndirectedGraphNode(curr->label));
        // copy neighbors to tmp
        for (auto gnode: curr->neighbors) st.push(shared_ptr<UndirectedGraphNode>(gnode));
        curr->neighbors.insert(curr->neighbors.begin(), tmp.get());
        visited.insert(curr->label);
    }
    // update neighbors
    visited.clear();
    st.push(s_node);
    while(!st.empty()) {
        shared_ptr<UndirectedGraphNode> curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) continue;
        for (vector<UndirectedGraphNode*>::iterator iter=curr->neighbors.begin() +1; iter!=curr->neighbors.end(); iter++) {
            curr->neighbors[0]->neighbors.push_back((*iter)->neighbors[0]);
            st.push(shared_ptr<UndirectedGraphNode>(*iter));
        }
        visited.insert(curr->label);
    }
    // split 
    visited.clear();
    UndirectedGraphNode* copy_head = node->neighbors[0];
    st.push(s_node);
    while(!st.empty()) {
        shared_ptr<UndirectedGraphNode> curr = st.top();
        st.pop();
        if (visited.find(curr->label) != visited.end()) curr->neighbors.erase(curr->neighbors.begin());
        visited.insert(curr->label);
    }
    return copy_head;
}