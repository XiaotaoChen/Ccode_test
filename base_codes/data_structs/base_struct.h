
#ifndef DATA_STRUCTS_
#define DATA_STRUCTS_

#include <stdio.h>

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

 struct RandomListNode {
     int label;
     RandomListNode* next;
     RandomListNode* random;
     RandomListNode(): label(-1), next(NULL), random(NULL) {}
     RandomListNode(int x): label(x), next(NULL), random(NULL) {}
 };


#endif // DATA_STRUCTS_