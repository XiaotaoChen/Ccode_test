
#ifndef DATA_STRUCTS_
#define DATA_STRUCTS_

#include <stdio.h>

struct TreeNode
{
    float value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : value(x), left(NULL), right(NULL) {}
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
 };


#endif // DATA_STRUCTS_