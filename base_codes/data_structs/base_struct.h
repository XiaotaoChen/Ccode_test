
#ifndef DATA_STRUCTS_
#define DATA_STRUCTS_

#include <stdio.h>
#include<vector>

struct TreeNode
{
    float val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
 };

 struct ListNode {
     int val;
     ListNode* next;
     ListNode(int x): val(x), next(NULL) {};
 };

  struct DoubleListNode {
     int val;
     DoubleListNode *left, *right;
     DoubleListNode(int x): val(x), left(NULL), right(NULL) {};
 };

struct DoubleListNodeLRU {
     int key, val;
     DoubleListNodeLRU *left, *right;
     DoubleListNodeLRU(int k, int v): key(k), val(v), left(NULL), right(NULL) {};
 };

 struct RandomListNode {
     int label;
     RandomListNode* next;
     RandomListNode* random;
     RandomListNode(): label(-1), next(NULL), random(NULL) {}
     RandomListNode(int x): label(x), next(NULL), random(NULL) {}
 };

struct UndirectedGraphNode {
    int label;
    std::vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct graphNode {
    int val;
    std::vector<graphNode*> neighbors;
    graphNode(): val(0), neighbors(std::vector<graphNode*>()) {}
    graphNode(int x): val(x), neighbors(std::vector<graphNode*>()) {}
    graphNode(int x, std::vector<graphNode*> _neighbors): val(x), neighbors(_neighbors) {}
};

#endif // DATA_STRUCTS_