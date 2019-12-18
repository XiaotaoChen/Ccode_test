#include <stdio.h>

struct TreeNode
{
    float value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : value(x), left(NULL), right(NULL) {}
};
