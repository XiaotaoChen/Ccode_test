#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
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
    std::printf("result:%d\n", result);
}

void test_postorderTraversal() {
    TreeNode* root = new TreeNode(1);
    TreeNode* r = new TreeNode(2);
    TreeNode* rr = new TreeNode(3);
    root->right = r;
    r->right = rr;
    vector<int> result;
    // binary_tree::postorderTraversal(root, result);
    binary_tree::postorderTraversalWithStack(root, result);
    for (int i=0; i<result.size(); i++) {
        std::printf("%d ,", result[i]);
    }
    std::printf("\n");
}

void test_generate_parentheses(int n){
    // vector<string> results = generate_parentheses(n);
    vector<string> results = generate_parentheses2(n);
    for (int i=0; i< results.size(); i++) {
        std::printf("%s \n", results[i].c_str());
    }
}

void test_reverse_polish_notation(){
    vector<string> tokens;
    // string inputs[5] = {"2", "1", "+", "3", "*"};
    string inputs[5] = {"4", "13", "5", "/", "+"};
    for (int i=0; i<5; i++) tokens.push_back(inputs[i]);
    int result = reverse_polish_notation(tokens);
    std::printf("%d \n", result);
}

void test_max_point_on_a_line(){
    vector<Point> inputs;
    inputs.push_back(Point(0, 0));
    int result = max_point_on_a_line(inputs);
    std::printf("%d \n", result);
}

void test_sortListNode(){
    ListNode* root = new ListNode(1);
    ListNode* tmp = root;
    tmp->next = new ListNode(2);
    tmp = tmp->next;
    tmp->next = new ListNode(3);
    tmp = tmp->next;
    tmp->next = new ListNode(4);
    tmp = tmp->next;
    tmp->next = new ListNode(5);
    tmp->next = root->next;
    ListNode* src = root;
    // while(src != NULL) {
    //     std::printf("%d ,", src->val);
    //     src = src->next;
    // }
    // std::printf("\n");

    // ListNode* result = list_node::sortList(root);
    // ListNode* result = list_node::insertSortList(root);
    // ListNode* result = list_node::reorderList(root);
    // ListNode* result = list_node::reorderList_V2(root);
    ListNode* result = list_node::detectCycle_V2(root);
    std::printf("%d ,", result->val);
    // while(result != NULL) {
    //     std::printf("%d ,", result->val);
    //     result = result->next;
    // }
    std::printf("\n");
}

void test_wordBreak(){
    string s = "catsanddog";
    std::unordered_set<string> dicts;
    // dicts.insert("leet");
    // dicts.insert("code");
    dicts = {"cat", "cats", "and", "sand", "dog"};
    // bool result = wordBreak(s, dicts);
    // printf("result:%d\n", result);
    // vector<string> result = wordBreak_v2(s, dicts);
    vector<string> result = wordBreak_v3(s, dicts);
    for(int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

int tmp_fetch(RandomListNode* head) {
    if (head != NULL) return head->label;
    return -1;
}

void print_random_list_node(RandomListNode* head) {
    RandomListNode* p = head;
    while(p != NULL) {
        printf("label:%d, next:%d, random:%d\n", p->label, 
               tmp_fetch(p->next), tmp_fetch(p->random));
        p = p->next;
    }
}

void test_randomListNode() {
    RandomListNode arr[5];
    for (int i=1; i<4; i++) {
        arr[i].label = i;
        arr[i].next = &arr[i+1];
        arr[i].random = &arr[i-1];
    }
    arr[0].next = &arr[1];
    arr[0].label = 0;
    arr[3].next = NULL;
    RandomListNode* head = &arr[0];
    print_random_list_node(head);
    RandomListNode* copy_head = list_node::copyRandomList(head);
    print_random_list_node(copy_head);
}

int main() {
    // test_minmum_depth_binary_tree();
    // test_generate_parentheses(3);
    // test_reverse_polish_notation();
    // test_max_point_on_a_line();
    // test_sortListNode();
    // test_postorderTraversal();
    // test_wordBreak();
    test_randomListNode();

    return 0;
}