#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include "data_structs/base_struct.h"
#include "algorithm.h"
#include "search_algs.h"
#include "dp_algs.h"
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

void test_singleNumber() {
    int a[7] = {1,2,3,2,3,2,3};
    // int result = singleNumber(a, 7);
    int result = singleNumber_v2(a, 7);
    printf("%d\n", result);
    return;
}

void test_candy() {
    int a[3]={2, 1, 3};
    vector<int> ratings(a, a+3);
    for(int i=0;i<ratings.size(); i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    int result = candy(ratings);
    printf("%d\n", result);
}

void test_complete_circuit() {
    // vector<int> gas(2);
    // vector<int> costs(2);
    // gas[0]=1;
    // gas[1]=2;
    // costs[0]=2;
    // costs[1]=1;
    int gas_arr[] = {1, 2};
    int costs_arr[] = {2, 1};
    vector<int> gas(gas_arr, gas_arr + 2);
    vector<int> costs(costs_arr, costs_arr + 2);
    int result = canCompleteCircuit_v2(gas, costs);
    printf("result:%d\n", result);
}

void test_clone_graph() {
    UndirectedGraphNode* zero = new UndirectedGraphNode(0);
    UndirectedGraphNode* one = new UndirectedGraphNode(1);
    UndirectedGraphNode* two = new UndirectedGraphNode(2);
    zero->neighbors.push_back(one);
    zero->neighbors.push_back(two);
    one->neighbors.push_back(two);
    two->neighbors.push_back(two);
    print_graph(zero);
    UndirectedGraphNode* copy_node = cloneGraph(zero);
    printf("clone graph\n");
    print_graph(copy_node);

    delete zero;
    delete one;
    delete two;
}

void test_palidrome() {
    string str = "aab";
    vector<vector<string> > result = palindrome_partition(str);
    printf("result size:%lu\n", result.size());
    for (vector<string> v_iter: result) {
        for (string iter: v_iter) {
            printf("%s,", iter.c_str());
        }
        printf("\n");
    }
}

void test_palidrome_min_cut() {
    string str = "leet";
    // int result = palindrome_minCut(str);
    int result = palindrome_minCut_v2(str);
    printf("result:%d\n", result);
}

void print_surroundReigon(vector<vector<char> >& board) {
    int width = board.size();
    int length = board[0].size();
    for (int i=0; i<width; i++) {
        for(int j=0; j<length; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void test_surroundRegion() {
    char board_arr[4][4] = {{'X','X','X','X'}, 
                            {'X','O','O','X'}, 
                            {'X','X','O','X'}, 
                            {'X','O','X','X'}};
    vector<vector<char> > board(4);
    for(int i=0; i<4; i++) {
        vector<char> tmp(board_arr[i], board_arr[i]+4);
        board[i] = tmp;
    }
    print_surroundReigon(board);
    SurroundingReigon(board);
    printf("\n");
    print_surroundReigon(board);
    return;
}

void test_sum_number_binary_tree() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    TreeNode* right = new TreeNode(3);
    root->left = left;
    root->right = right;
    int sum = binary_tree::sumNumbers(root);
    printf("sum:%d\n", sum);
}

void test_longest_consecutive() {
    int arr[] = {100, 4, 200, 1, 3, 2};
    vector<int> vec(arr, arr+6);
    // int result = longestConsecutive(vec);
    int result = longestConsecutive_V2(vec);
    printf("result:%d\n", result);
}

void test_ladder_length() {
    std::string start = "hit";
    std::string end = "cog";
    std::unordered_set<std::string> dict {"hot","dot","dog","lot","log"};
    // std::string start = "teach";
    // std::string end = "place";
    // std::unordered_set<std::string> dict {"peale","wilts","place","fetch","purer","pooch","peace","poach","berra","teach","rheum","peach"};
    // int result = search::ladderLength(start, end, dict);
    // printf("result:%d\n", result);

    std::vector<std::vector<std::string> > result = search::findLadders_V2(start, end, dict);
    for(int i=0;i<result.size(); i++) {
        for(int j=0; j<result[i].size(); j++) {
            printf("%s ", result[i][j].c_str());
        }
        printf("\n");
    }
}

void test_queue_vector() {
    std::queue<std::vector<std::string> > qu;
    std::vector<std::string*> str_vec(4);
    std::string str1 = "str1";
    std::string str2 = "str2";
    printf("str1 add:%p, str2 add:%p\n", &str1, &str2);
    str_vec.push_back(&str1);
    printf("str_vec add:%p str_vec[size -1] add:%p, size:%lu\n", str_vec.front(), str_vec[str_vec.size()-1], str_vec.size());
    printf("str_vec[size-1]:%s\n",(*(str_vec[str_vec.size()-1])).c_str());
    // qu.push(str_vec);

    str_vec.push_back(&str2);
    printf("str_vec add:%p str_vec[size -1] add:%p, size:%lu\n", str_vec.front(), str_vec[str_vec.size()-1], str_vec.size());
    printf("str_vec[size-1]:%s\n", (*(str_vec[str_vec.size()-1])).c_str());
    // printf("%d\n", qu.front().size());
}
void test_is_palindrome() {
    std::string s = "A man, a plan, a canal: Panama";
    bool result = search::isPalindrome(s);
    printf("result:%d\n", result);
}

void test_maxPathSum() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    int result = search::binary_tree::maxPathSum(root);
    printf("result:%d\n", result);
}

void test_maxprofix() {
    int arr[] = {3,2,1,3,4,5,4,6,1,7};
    std::vector<int> vec(arr, arr+10);
    int result = search::maxProfit_v3(vec);
    printf("result:%d\n", result);
}

void test_minimumTotal() {
    std::vector<std::vector<int> > triangle;
    int line1[]={2};
    int line2[]={3,4};
    int line3[]={6,5,7};
    int line4[]={4,1,8,3};
    std::vector<int> line1_v(line1, line1+1);
    std::vector<int> line2_v(line2, line2+2);
    std::vector<int> line3_v(line3, line3+3);
    std::vector<int> line4_v(line4, line4+4);
    triangle.push_back(line1_v);
    triangle.push_back(line2_v);
    triangle.push_back(line3_v);
    triangle.push_back(line4_v);

    int result = dp::minimumTotal(triangle);
    printf("result:%d\n", result);
}

void test_pascal_row() {
    // std::vector<int> result = dp::getRow(3);
    // for (int i=0; i<result.size(); i++) {
    //     printf("%d, ", result[i]);
    // }
    // printf("\n");

    std::vector<std::vector<int> > result = dp::generate(3);
    for (int i=0; i<result.size(); i++) {
        for(int j=0; j<=i; j++) {
            printf("%d ",result[i][j]);
        }
        printf("\n");
    }
}

void test_populating_next_right_pointer() {
    TreeLinkNode* root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2);
    root->right = new TreeLinkNode(3);
    // root->left->left = new TreeLinkNode(4);
    root->left->right = new TreeLinkNode(5);
    // root->right->left = new TreeLinkNode(6);
    // root->right->right = new TreeLinkNode(7);
    search::populating_next_right_pointers_in_each_node(root);

    TreeLinkNode* curr_left=root;
    while(curr_left != nullptr) {
        TreeLinkNode* curr = curr_left;
        while(curr != nullptr) {
            printf("%d ", curr->val);
            curr = curr->next;
        }
        printf("\n");
        curr_left = curr_left->left;
    }

    delete root->right->right;
    delete root->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
}

void test_min_distance_of_string() {
    std::string S = "rabbbit"; // ""rabbbit";
    std::string T = "rabbit"; // "rabbit";
    int result = dp::min_distance_of_str(S, T);
    printf("result:%d\n", result);
}

void test_haspathsum() {
    TreeNode* root = new TreeNode(-2);
    root->left = new TreeNode(-3);
    // root->right = new TreeNode(1);
    // root->left->right = new TreeNode(11);
    // root->right->left = new TreeNode(13);
    // root->right->right = new TreeNode(4);
    int sum = -5;
    bool result = search::hasPathSum(root, sum);
    printf("result:%d\n", result);
    std::vector<std::vector<int>> results = search::pathSum(root, sum);
    // std::vector<std::vector<int>> results = search::pathSum_bfs(root, sum);
    for (int i=0; i< results.size(); i++) {
        for(int j=0; j<results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // test_minmum_depth_binary_tree();
    // test_generate_parentheses(3);
    // test_reverse_polish_notation();
    // test_max_point_on_a_line();
    // test_sortListNode();
    // test_postorderTraversal();
    // test_wordBreak();
    // test_randomListNode();
    // test_singleNumber();
    // test_candy();
    // test_complete_circuit();
    // test_clone_graph();
    // test_palidrome();
    // test_palidrome_min_cut();
    // test_surroundRegion();
    // test_sum_number_binary_tree();
    // test_longest_consecutive();
    // test_ladder_length();
    // test_queue_vector();
    // test_is_palindrome();
    // test_maxPathSum();
    // test_maxprofix();
    // test_minimumTotal();
    // test_pascal_row();
    // test_populating_next_right_pointer();
    // test_min_distance_of_string();
    test_haspathsum();

    return 0;
}