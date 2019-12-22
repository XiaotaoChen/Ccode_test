#include <cstdio>
#include <vector>
#include <string>
#include "data_structs/base_struct.h"
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

void test_reverse_polish_notation(){
    vector<string> tokens;
    // string inputs[5] = {"2", "1", "+", "3", "*"};
    string inputs[5] = {"4", "13", "5", "/", "+"};
    for (int i=0; i<5; i++) tokens.push_back(inputs[i]);
    int result = reverse_polish_notation(tokens);
    printf("%d \n", result);
}

void test_max_point_on_a_line(){
    vector<Point> inputs;
    inputs.push_back(Point(0, 0));
    int result = max_point_on_a_line(inputs);
    printf("%d \n", result);
}

int main() {
    // test_minmum_depth_binary_tree();
    // test_generate_parentheses(3);
    // test_reverse_polish_notation();
    test_max_point_on_a_line();
    
}