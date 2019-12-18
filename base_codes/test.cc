#include <stdio.h>
#include <algorithm>  // min
#include "data_structs/Tree.h"
using namespace std;

int run(TreeNode *root) {
    if (root == NULL) return 0;
    if (root->left == NULL) return run(root->right) + 1;
    else if (root->right == NULL) return run(root->left) + 1;
    int left_high = run(root->left) + 1;
    int right_high = run(root->right) + 1;
    return min(left_high, right_high);
}

int main() {
    TreeNode* root = new TreeNode(0);
    TreeNode* left1 = new TreeNode(1);
    TreeNode* right1 = new TreeNode(2);
    TreeNode* right2 = new TreeNode(3);
    root->left = left1;
    root->right = right1;
    right1->right = right2;
    int result = run(root);
    printf("result:%d\n", result);
}