#include <cstdio>
#include <vector>
#include <string>
#include "data_structs/Tree.h"
#include "algorithm.h"
using namespace std;

void test_minmum_depth_binary_tree() {
    TreeNode* root = new TreeNode(0);
    TreeNode* left1 = new TreeNode(1);
    // TreeNode* right1 = new TreeNode(2);
    // TreeNode* right2 = new TreeNode(3);
    root->left = left1;
    // root->right = right1;
    // right1->right = right2;
    // int result = binary_tree::minimum_depth_binary_tree(root);
    int result = binary_tree::minimum_depth_binary_tree_by_queue(root);
    printf("result:%d\n", result);
}

void test_generate_parentheses(int n){
    // vector<string> results = generate_parentheses(n);
    vector<string> results = generate_parentheses2(n);
    for (int i=0; i< results.size(); i++) {
        printf("%s \n", results[i].c_str());
    }
}

int main() {
    // test_minmum_depth_binary_tree();
    test_generate_parentheses(3);
}