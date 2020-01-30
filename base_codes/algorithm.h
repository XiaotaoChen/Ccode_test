
#ifndef ALGORITHM_
#define ALGORITHM_
#include <vector>
#include <string>
#include <unordered_set>
#include "data_structs/base_struct.h"

using namespace std;

namespace  binary_tree {
    int minimum_depth_binary_tree(TreeNode* root);
    int minimum_depth_binary_tree_by_queue(TreeNode* root);
    int minimum_depth_binary_tree_by_queue2(TreeNode* root);
    void postorderTraversal(TreeNode *root, vector<int>& result);
    void postorderTraversalWithStack(TreeNode *root, vector<int>& result);
    int sumNumbers(TreeNode *root);

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
    RandomListNode* copyRandomList(RandomListNode* head);
}

bool wordBreak(string s, unordered_set<string> &dict);

vector<string> wordBreak_v2(string s, unordered_set<string> &dict);

vector<string> wordBreak_v3(string s, unordered_set<string> &dict);

int singleNumber(int A[], int n);

int singleNumber_v2(int A[], int n);

int singleNumber_v3(int A[], int n);

int candy(vector<int> &ratings);

int canCompleteCircuit(vector<int> &gas, vector<int> &cost);

int canCompleteCircuit_v2(vector<int> &gas, vector<int> &cost);

UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node);

UndirectedGraphNode* cloneGraph_v2(UndirectedGraphNode* node);

void print_graph(UndirectedGraphNode* node);

vector<vector<string> > palindrome_partition(string& str);

bool is_palindrome(string& str);

int palindrome_minCut(string& str);

int palindrome_minCut_v2(string& str);

void SurroundingReigon(vector<vector<char> >& board);

int longestConsecutive(vector<int> &num);

int longestConsecutive_V2(vector<int> &num);

#endif // ALGORITHM_