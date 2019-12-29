
#ifndef ALGORITHM_
#define ALGORITHM_
#include <vector>
#include <string>
#include "data_structs/base_struct.h"

using namespace std;

namespace  binary_tree {
    int minimum_depth_binary_tree(TreeNode* root);
    int minimum_depth_binary_tree_by_queue(TreeNode* root);
    int minimum_depth_binary_tree_by_queue2(TreeNode* root);
    void postorderTraversal(TreeNode *root, vector<int>& result);
    void postorderTraversalWithStack(TreeNode *root, vector<int>& result);

} // binary_tree

vector<string> generate_parentheses(int n);
vector<string> generate_parentheses2(int n);

int reverse_polish_notation(vector<string> &tokens);

int max_point_on_a_line(vector<Point> &points);

namespace list_node {
    ListNode* sortList(ListNode* head);
    ListNode* getmid(ListNode* head);
    ListNode* merge_list(ListNode* list1, ListNode* list2);
    ListNode* insertSortList(ListNode* head);
    ListNode* reorderList_V2(ListNode* head);
    ListNode* detectCycle(ListNode* head);
    ListNode* isCycle(ListNode* head);
    ListNode* detectCycle_V2(ListNode* head);
}

#endif // ALGORITHM_