#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cstdlib> // rand, qsort
#include <functional>
#include <fstream>
#include "data_structs/base_struct.h"
#include "algorithm.h"
#include "sorts.h"
#include "utils.h"
#include "search_algs.h"
#include "dp_algs.h"
#include "greedy_algs.h"
#include "graph_algs.h"
#include "trace_back_algs.h"
#include "dfs_algs.h"
#include "bfs_algs.h"
#include "stack_algs.h"
#include "heap_algs.h"
#include "binary_search.h"
#include "merge_set.h"
#include "listnode_algs.h"
#include "binary_pointer.h"
#include "str_algs.h"
#include "topoloical_sort.h"
#include "memory_algs.h"
#include "hash_algs.h"
#include "bits_algs.h"
#include "design_algs.h"
#include "dict_tree.h"
#include "line_tree_algs.h"
#include "minimization_algs.h"
#include "random_sample_algs.h"
#include "geometric_algs.h"
#include "swordfingeroffer.h"
#include "queue_algs.h"
#include "hot_100.h"
#include "thot_50.h"

using namespace std;

/*
1.求树的最小深度：
递归： 若左右子树均不为null，则等于min(left_depth, right_depth) + 1;
queue: for (q.size()) q.pop(), 逐层遍历直到某个node的左右子树均为null，每遍历一遍则depth+1。
*/
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

/*
2. 后序遍历：
递归，
stack： 遍历root->val, root->right, root->left, 最后reverse 整个result数组。
*/
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

/*
3. 使用stack求逆波兰式
*/
void test_reverse_polish_notation(){
    vector<string> tokens;
    // string inputs[5] = {"2", "1", "+", "3", "*"};
    string inputs[5] = {"4", "13", "5", "/", "+"};
    for (int i=0; i<5; i++) tokens.push_back(inputs[i]);
    int result = reverse_polish_notation(tokens);
    std::printf("%d \n", result);
}

/*
4. 求最大共线点数：两层循环，分别求以点i为起点的最大共线点数。因为浮点数存在误差，斜率需要用向量表示，向量可由x,y除以最大公约数得到。并额外处理斜率为0，无穷大，及重合的点。
最大公约数：max_common_divisor(a,b) if (a%b==0) return b; else return max_common_divisor(b, a%b);
*/
void test_max_point_on_a_line(){
    vector<Point> inputs;
    inputs.push_back(Point(0, 0));
    int result = max_point_on_a_line(inputs);
    std::printf("%d \n", result);
}

/*
5. 对链表进行排序，使用二分法 + merge two listnode
6. 检测链表中是否存在环，并找出环的起点。（1）通过step=1,2两个指针遍历链表，若两者相等，则存在环，返回该重合的点；（2）分别从起点，重合的点以step=1走，当起点走到重合点时，
   则重合点的指针刚好走到环的起始位置。画可知，step=2的指针比step=1的指针多走的具体就是起点到重合点的距离== 重合点到环起点的距离。
*/
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

/*
7. 求得字符串由dicts中子串拆分的所有可能。
(1) dp[n]数组保存0到i的子串是否可由dicts中的构成。两重for循环(i=1->n-1, j=0->i) if (dp[j] && s.substr(j, i-j+1) in dict) dp[i]=true
(2) 根据dp由n反推到0，得到所有的子串。dfs(idx, dp[], result): for (i=idx-1->0) {if dp[i] && s.substr(i, idx-i+1) in dict} result[i]=result[idx] + substr, dfs(i-1, dp, result);
再刷感想：1. 使用dp求得０->i是否可由dicts中的字符串组成，并记录其前一个节点下标，如dp[6]从dp[3]得到，则traces[6].push_back(3);
        2. 根据dp flags 和traces, 可以构建整个字符串的结果．注意区分０，和第０个元素．为直观起见，在０的时候单独判断，而不是new len+1个空间区分
*/
void test_wordBreak(){
    string s = "catsanddog";
    std::unordered_set<string> dicts;
    // dicts.insert("leet");
    // dicts.insert("code");
    dicts = {"cat", "cats", "and", "sand", "dog"};
    // bool result = wordBreak(s, dicts);
    // printf("result:%d\n", result);
    // vector<string> result = wordBreak_v2(s, dicts);
    // vector<string> result = wordBreak_v3(s, dicts);
    vector<string> result = dp::wordBreak(s, dicts);
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

/*
8. 复制待随机指针的链表：这类指针复制分三步：
（1） 克隆节点，并插入原始节点中。即 src->next = src_copy; scr_copy->next = src->next;
 (2) 设置指针连接关系。即src_copy->random = src->random->next;
 (3) 分离src/copy
*/
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

/*
9. 从重复2次，3次的数组中找出唯一出现一次的数。
（1）重复两次，则相同的数按位异或会变0，所以异或所有的数，最终结果就为只出现一次的数。for(num=A[0]-->A[n]) result ^= num;
 (2) 重复三次，则使用one, two, three三个变量分别记录出现1，2，3次的每一比特，最终返回one即可。
     one=two=three=0;
     for（num=A[0]-->A[n]） {
         two |= (one & num); // 一个数出现两次
         one ^= num; // 某一比特位位1的条件
         three = one & two; // 出现三次的情况
         one &= ~three; // 如果出现三次，则将one对应位置0
         two &= ~three; // 如果出现三次，则将two对应位置0
     }
*/
void test_singleNumber() {
    int a[7] = {1,2,3,2,3,2,3};
    // int result = singleNumber(a, 7);
    int result = singleNumber_v2(a, 7);
    printf("%d\n", result);
    return;
}

/*
10. n个小朋友分糖，rating高的人必须比旁边低的人分的多，每人最少一个。
从1遍历到最后
如果当前rating大于前一个，则当前分糖数为前一个+1；
否则：从前一个节点一直往前遍历：直到不满足： ranting[j]>ranting[j+1] && result[j]<=result[j+1]： result[j]=result[j+1]+1;
*/
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

/*
11. 汽车是否能走完全程，并找到起点位置。
（1）start为n,end为0，如果res + cost[start]-gas[start]<0,则说明该点不能作为起点，start--；否则end++；直到start==end结束，即为该点。
*/
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

/*
12. 同8
*/
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

/*
13. 将字符串分割成回文子串的所有可能,每次回溯需要pop_back curr_vector。dfs(curr_str, curr_vector, result): for (i=0->curr_str.length()) 
    if (curr_str(0,i+1) is palindrome) curr_vector.push_back(curr_str(0,i+1)); dfs(curr_str(i,len-1), curr_vector, result);
*/
void test_palidrome() {
    string str = "aab";
    // vector<vector<string> > result = palindrome_partition(str);
    vector<vector<string> > result = dfs::palindrome_partition(str);
    printf("result size:%lu\n", result.size());
    for (vector<string> v_iter: result) {
        for (string iter: v_iter) {
            printf("%s,", iter.c_str());
        }
        printf("\n");
    }
}

/*
14. 最小回文子串的数量：两重循环，i=0->n;j=i->n; if (s.sub(i, j-i+1) is palindrome) dp[j]=min(dp[j],dp[i]+1)
再刷感想：1. 使用dp求解．如果str[i]!=str[j], dp[i,j] = min(dp[i,j], dp[i][k]+dp[k+1][j]), 如果str[i]==str[j] dp[i,j]=dp[i+1,j-1], 注意j-1>2
*/
void test_palidrome_min_cut() {
    string str = "leet";
    // int result = palindrome_minCut(str);
    // int result = palindrome_minCut_v2(str);
    int result = dp::palindrome_minCut(str);
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

/*
15. 保留边界‘0’的连通部分。使用queue/stack遍历边界‘0’部分，置为‘A’
*/
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

/*
16. 找出最长连续数的个数。使用set/map存所有的数，遍历arr，得到第i个val， 依次val--， val++ 从set/map中找
*/
void test_longest_consecutive() {
    int arr[] = {100, 4, 200, 1, 3, 2};
    vector<int> vec(arr, arr+6);
    // int result = longestConsecutive(vec);
    int result = longestConsecutive_V2(vec);
    printf("result:%d\n", result);
}

/*
17. 去掉空格，标点符号，屏蔽大小写差异，判断是否为回文串。
（1）遍历字符串去掉空格，标点符号；interview 48 最长不重复的子字符串
（2）转成小写字符，std::transform(begin(), end(), ::tolower);
（3）判断是否为回文串，即str==std::string(str.rbegin(), str.rend())
*/
void test_is_palindrome() {
    std::string s = "A man, a plan, a canal: Panama";
    bool result = search::isPalindrome(s);
    printf("result:%d\n", result);
}

/*
18. 求二叉树最大的路径之和。dfs
当前节点的最大路径之和=val + left_node_result + right_node_result;
return val + max(left_node_result, right_node_result);
再刷感想：1.dfs过程中要计算两个值：１．包含当前节点的单边path的最大值，２．包含当前节点的最大路径之和．
２．因为是可以选择任意节点，所以只有在路径大于零时才将该路径并入，单边path,最大路径和都需要比较左右子树的路径大小是否＞０
*/
void test_maxPathSum() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    // int result = search::binary_tree::maxPathSum(root);
    int result = search::binary_tree::maxPathSum_V2(root);
    printf("result:%d\n", result);
}

/*
19. 买卖两次股票，收益最大能到多少。
使用buy1, sell1,buy2,sell2模拟两次交易的内容。
buy1=max(buy1, -prices[i]); 买入股票需要掏出的钱，越少越好
sell1=max(sell1, buy1+prices[i]); 卖出股票，剩余的钱越多越好;
buy2=max(buy2, sell1-prices[i]); 第二次买入股票
sell2=max(sell2, buy2+prices[i])
*/
void test_maxprofix() {
    int arr[] = {3,2,1,3,4,5,4,6,1,7};
    std::vector<int> vec(arr, arr+10);
    int result = search::maxProfit_v3(vec);
    printf("result:%d\n", result);
}

/*
20. 求三角形从上到下最小的路径之和。其中只能和其相邻的数相加。
动态规划 dp[2][line]
*/
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

/*
21. 生成杨辉三角
*/
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

/*
22. 给二叉树兄弟节点加上next指针。
通过queue依次得到每一层的所有节点，然后将依次设置节点的next指针。
*/
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

    // delete root->right->right;
    // delete root->right->left;
    // delete root->left->right;
    // delete root->left->left;
    // delete root->left;
    // delete root->right;
    // delete root;
}

/*
23. 求两个字符串的最短距离，dp求解，根据代码没看懂问题的定义
*/
void test_min_distance_of_string() {
    std::string S = "rabbbit"; // ""rabbbit";
    std::string T = "rabbit"; // "rabbit";
    int result = dp::min_distance_of_str(S, T);
    printf("result:%d\n", result);
}

/*
24. 遍历二叉树的路径，判断是否存在和为sum的路径，并返回所有可能的路径结果
回溯法。bfs(combinations, curr, res, root)
将val push curr
如果res==root->val && root->left==null && root->right==null 则将curr push到结果中；
bfs(combinations, curr, res, root->left)
bfs(combinations, curr, res, root->right)
*/
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


/*
25. 快速排序，堆排序
快排： 先从j开始，while(arr[j]<=ref&& i<j)j--; arr[j]=arr[i];
堆排序： 先构建最大堆。从k=2/length-1-->0调整堆的顺序；
然后依次从length-1->1, 交换arr[0],arr[i]的值，调整堆的顺序；
heap_modify: 注意dad=start，son=2*dad+1; while(son<=end) {
    找到左右子节点最大的一个，如果son的值大于dad的交换两者，dad=son；son=2*dad+1；
    否则直接返回。
}
*/
void test_qsort() {
    // int a[] = {6, 2, 1, 3, 5, 4};
    int len = 20;
    int a[len];
    int b[len];
    // int a[] = {3, 6, 7, 5, 3, 5, 6, 2, 9, 1};
    for (int i=0; i<len; i++) {
        a[i] = std::rand() % len;
        b[i] = a[i];
    }
    for (int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    std::qsort(b, len, sizeof(int), utils::compare);
    for(int i=0; i<len; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // sort::qsort(a, 0, len -1);
    // sort::heap_sort(a, 0, len-1);
    // sort::qsort_v2(a, 0, len-1);

    std::vector<int> a_vec = std::vector<int>(a, a+len);

    sort::qsort_v3(a_vec);
    for (int i=0; i<len; i++) {
        printf("%d ", a_vec[i]);
    }
    printf("\n");
}

/*
26. 两个链表数字相加。
1.将两个链表对应位分别相加，合成一个链表后再转成正常数字。注意最后一位是否进位的问题。
2.将两个链表对应位相加，使用carry位保留前一位的进位，在相加过程中完成进位。
*/
void test_add_two_numbers() {
    ListNode* l1 = new ListNode(9);
    l1->next = new ListNode(8);
    // l1->next->next = new ListNode(3);
    ListNode *l2 = new ListNode(1);
    // l2->next = new ListNode(6);
    // l2->next->next = new ListNode(4);
    ListNode *result = search::addTwoNumbers_v2(l1, l2);
    while(result != nullptr) {
        printf("%d ", result->val);
        result = result->next;
    }
}

/*
27. 从两个有序数组中找出中位数。
1. 先对两个数组merge，然后直接找出中位数。
2. 二分查找。每次查找两个数组中的k/2个，直接舍弃较小的那一部分。
dfs(nums1, low1, nums2, low2, k);
注意k==1，low1,low2是否在nums1,nums2之内。
if (low1+k/2-1<nums1.size())mid1=nums1[low1+k/2-1];
if (low2+k/2-1<nums2.size()) mid2 = nums2[low2+k/2-1];
if (mid1<mid2) dfs(nums1, low1+k/2, nums2, low2, k-k/2);
else dfs(nums1, low1, nums2, low2+k/2, k-k/2);
*/
void test_find_mid_num() {
    std::vector<int> a={1, 3};
    std::vector<int> b={2};
    // double result = search::findMedianSortedArrays(a, b);
    double result = search::findMedianSortedArrays_v2(a, b); 
    printf("result:%f \n", result);
}

/*
28. 求字符串中最长的回文子串。
dp[][] 记录i->j是否为回文串
dp[i][j]与 dp[i+1][j-1]的关系，注意考虑a|a,aba两者情况
*/
void test_length_palindrome() {
    std::string str = "abaabca"; //"abcdasdfghjkldcba";
    // std::string result = search::longestPalindrome(str);
    // std::string result = dp::longestPalindrome_v2(str);
    // std::string result = dp::longestPalindrome_v3(str);
    // std::string result = dp::longestPalindrome_v4(str);
    std::string result = dp::longestPalindrome_v5(str);
    printf("result: %s\n", result.c_str());
}


/*
29. 字符按照N字形排列，按行输出最后的顺序。
推导出N字排列的规律。一个周期为2*rows-2,
钱rows个为列，后面row-2个斜向上递增。
*/
void test_z_convert() {
    std::string str = "LEETCODEISHIRING";
    int rows = 4;
    std::string result = search::z_convert(str, rows);
    printf("result:%s\n", result.c_str());
}

/*
30. 数字转换
1. 特殊处理第一个字符，判断是否存在正负号
2. 使用double保存中间结果避免int溢出，然后对int32_max,int32_min进行判断
*/
void test_my_atoi() {
    std::string str= "-2147483647";
    int result = search::myAtoi(str);
    printf("result:%d\n", result);
}

/*
31. 正则表达式匹配
dp求解：dp[i][j]表示s的前i个字符与p的前j个字符是否匹配。
注意*匹配0个字符的情况。初始化i=0的情况，if p[j]='*' p[j]=p[j-2]

注意: 1. ＊号匹配要满足s[idx]==p[j], 
     2. 字符下标和dp下标
     3. 初始化dp[0][i]的时候，考虑*匹配０个字符的情况，
     如果p[i-1]=='*', dp[0][i]应该等于dp[0][i-2], 而不是直接等于true

再刷感想：1. 必须有dp[n+1,m+1]即匹配０个元素的状态，否则无法处理s＝＂＂，p=".*"这种
　　　　　２．匹配０个字符情况下特殊处理，且返回值为dp[n][m]
        3. 在匹配>=1个字符时，s[idx]与p[j]要match
再刷感想：1. p[j]!='*'时，s[i－１]与p[j－１]匹配时，dp[i][j]=dp[i-1][j-1]，而不是直接为true
*/
void test_regular_match() {
    std::string s= "aa"; //"aab"; //"acbbcbcbcbaaacaac"; //"aab"; //"issi"; //"mississippi";
    std::string p = "a"; //"c*a*b"; //"ac*.a*ac*.*ab*b*ac"; //"c*a*b"; //"is*"; // "mis*is*p*.";
    // bool result = dp::regular_match(s, p);
    // bool result = dp::regular_match_v2(s, p);
    // bool result = dp::regular_match_v3(s, p);
    bool result = dp::regular_match_v4(s, p);
    printf("result:%d\n", result);
}

/*
32. 最大的矩形面积
1.维护一个升序的栈，纪录对于数字的index，当当前数值>stack.top()时，直接push
2.当小于时，记录以当前栈顶元素为高，i-当前栈顶元素前一个元素的idx
3.最后依次pop stack中的元素，(len-i)* high
再刷心得：维护一个升序栈，当前元素小于栈顶元素时，一直pop,并计算area,而不是只pop 一次栈顶元素．
*/
void test_largest_rectangle_area() {
    std::vector<int> arr = {2,1,5,6,2,3}; //{4, 1000, 1000, 1000, 1000};  // {7, 2, 1, 4, 5, 1, 3, 3}; // {3, 1, 6, 5, 2, 3}; // {2,1,5,6,2,3};
    // int result = search::largestRectangleArea(arr);
    int result = stack_algs::largestRectangleArea(arr);
    printf("result:%d\n", result);
}

/*
33. 求最大方阵长度
dp求解dp[i][j]表示0,0-->i,j部分最大方阵的长度。
dp[i][j]=min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1
*/
void test_maximal_square() {
    std::vector<std::vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                             {'1', '0', '1', '1', '1'},
                                             {'1', '1', '1', '1', '1'},
                                             {'1', '0', '0', '1', '0'}};
    int result = dp::maximalSquare(matrix);
    printf("result:%d\n", result);
}

/*
34. 求水箱的最大容量
从两边往中间依次遍历即可。
*/
void test_max_area_in_water_tank() {
    std::vector<int> arr= {1,8,6,2,5,4,8,3,7}; //{1,2,4,3}; // {1,2}; // {1,8,6,2,5,4,8,3,7};
    // int result = search::maxArea(arr);
    // int result = search::maxArea_v2(arr);
    int result = search::maxArea_v3(arr);
    printf("result:%d\n", result);
}

/*
35. 转换成罗马数字
建立一个<int, string>的map，
列举所有可能的值：1，4，5，9.... 对应的string "I", "IV"
降序排列。
*/
void test_int_to_map() {
    // std::string result = search::intToRoman_v2(1994);
    std::string result = search::intToRoman_v3(1994);
    
    printf("result:%s\n", result.c_str());
}

/*
36. 判断一棵数是不是另一棵树的子树
需要额外判断子树是否相等。因为是否是子树必须是两者相等。
if （root->val!=sub->val） 
(issame(root->left, sub->left)&& issame(root->right, sub->right)||
isSub(root->left, sub)||isSub(root->right, sub)
else:
isSub(root->left, sub)||isSub(root->right, sub)
)
*/
void test_is_subtree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->right->left = new TreeNode(2);
    // root->left->left = new TreeNode(0);
    TreeNode* sub = new TreeNode(3);
    sub->left = new TreeNode(1);
    sub->right = new TreeNode(2);
    bool result = search::isSubtree(root, sub);
    printf("result:%d\n", result);
}

/*
37. 找到两个节点最近的公共祖先
递归判断一棵树中是否存在p或q节点
left = dfs(root->left, p,q)
right = dfs(root->right, p,q);
if (left==null&& right==null) return null
if(left!=null && right!=null) return root //左右节点均存在p或q
if (left!=null && right==null) return left // 只有left存在p或q
if (left==null && right!=null) return right
*/
void test_is_lowest_ancestor() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    TreeNode* p = root->left;
    TreeNode* q = root->left->right->right;
    TreeNode* result = search::lowestCommonAncestor2(root, p, q);
    printf("result:%lf\n", result->val);
}

/*
38. 找到树中所有可能到sum，并返回出现次数最多的元素
*/
void test_requent_tree_sum() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(-5);
    // root->left->left = new TreeNode(6);
    // root->left->right = new TreeNode(2);
    // root->left->right->left = new TreeNode(7);
    // root->left->right->right = new TreeNode(4);
    // root->right->left = new TreeNode(0);
    // root->right->right = new TreeNode(8);
    std::vector<int> result = search::findFrequentTreeSum(root);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
39. 简化路径
1. 以‘/’划分字符子串得到items。
2. 遍历items，依次将item压入栈中，当出现'..'时pop；
3. 依次弹出item，result = '/' + item + result;
再刷感想：注意分词时别漏了最后一个词．
*/
void test_simple_path() {
    std::string path = "/a//b////c/d//././/.."; //"/a/../../b/../c//.//"; // "/a/./b/../../c/"; // "/home//foo/"; // "/../"; // "/home/";
    // std::string result = search::simplifyPath(path);
    std::string result = search::simplifyPath_V2(path);
    printf("result:%s\n", result.c_str());
}


/*
40. 反转链表m,n之间的元素
1. 记录m的前一个元素和m元素的指针。然后从m+1个元素开始，
node(m+1)->next=node(m-1)->next;
node(m-1)->next = node(m+1);
2. 在n的时候，node(m)->next=node(n)->next;
*/
void test_reverse_between() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* result = search::reverseBetween(head, 2, 2);
    while(result!=nullptr) {
        printf("%d ", result->val);
        result = result->next;
    }
    printf("\n");
}

/*
41. 判断4个数是否可以求得24点
1. 递归求解，先从4个数中选取两个数进行一直运算得到结果，
然后从3个数中选两个得到结果，最终只剩一个数时，判断是否等于24
*/
void test_juge_point24() {
    // std::vector<int> nums = {1, 2, 1, 2}; // {4, 1, 8, 7};
    // bool result = search::judgePoint24(nums);
    std::vector<double> nums = {4, 1, 8, 7};
    char op_types[5] = {'*', '+', '/', '-'};
    bool result = search::judgePoint24_v2(nums, op_types);
    printf("result:%d\n", result);
}

/*
42. 矩阵旋转遍历
模拟旋转遍历，注意i,j是否越界
*/
void test_spiral_order() {
    std::vector<std::vector<int>> matrix = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}}; // {{1,2,3}, {4,5,6}, {7,8,9}};
    std::vector<int> result = search::spiralOrder(matrix);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
43. 生成旋转矩阵
与42类似
*/
void test_generate_matrix(){
    std::vector<std::vector<int>> result = search::generateMatrix(3);
    for (int i=0; i< result.size(); i++) {
        for (int j=0; j<result[0].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/*
43. 找出递增数组中val与idx一致的数。
递增数组中val与idx一致的数只可能出现连续的一次。不可能出现多次。
mid = (left+right)/2
// 左边不可能存在符合条件的数
if num[mid]<mid: dfs(mid+1, right)
else dfs(left, mid-1)
*/
void test_match_idx_val() {
    std::vector<int> data = {-5,1,2,3,6};
    std::vector<int> result;
    search::match_idx_val(data, result, 0, 4);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    result.clear();
    search::match_idx_val_v2(data, result, 0, 4);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
44. 求所有二叉树非叶子节点总和的最小值。
dp求解。定义辅助数组aux[i][j]表示i->j元素中最大的值
dp[i][j]表示i->j中总和最小值，则dp[i][j]=min(dp[i][k]+dp[k][j])+ aux[i][k]*aux[k][j];
*/
void test_mct_from_leaf() {
    std::vector<int> data= {6,2,4};
    int result = dp::mctFromLeafValues(data);
    printf("result:%d\n", result);
}


/*
45. 三数之和
先对数组排序，设置first，second,thrid指针，不能指向重复的元素
for (int i=0; i<n-2; i++) {
    secod=i+1;
    third = n-1;
    if (nums[first]+nums[secod]==target-nums[third])....
}
注意：1. 不指向重复元素时，　要判断second 始终小于third. 同时该操作只需要在
nums[first]+nums[second] == target - nums[third]时做，而不需要在外面也判断，
因为second+, third--即可达到同样目的．
*/
void test_three_sum() {
    std::vector<int> data = {-1, 0, 1, 2, -1, -4}; //{-2,0,0,2,2}; //{-1, 0, 1, 2, -1, -4};
    // std::vector<std::vector<int>> result = search::threeSum(data);
    // std::vector<std::vector<int>> result = search::threeSum_v2(data);
    std::vector<std::vector<int>> result = search::threeSum_v3(data);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/*
46. 田忌赛马
1.对A，B进行排序。2.注意B中可能存在重复的元素。
if A[j]> B[i]:match_map[B[i]].push(A[j]);
else: unmatch.push(A[j]);
*/
void test_advantage_count() {
    std::vector<int> A = {2,0,4,1,2}; // {12,24,8,32}; //{2,7,11,15};
    std::vector<int> B = {1,3,0,0,2}; // {13,25,32,11}; // {1,10,4,11};
    std::vector<int> result = greedy::advantageCount(A, B);
    for (int i=0;i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
47. 判断是否可以跳到终点
记录当前可到达的最远点k=max(k, nums[i]+i)
*/
void test_can_jump() {
    std::vector<int> data = {3,2,1,0,4}; //{2,3,1,1,4};
    // bool result = greedy::canJump(data);
    // printf("result:%d\n", result);
    int result = greedy::jump(data);
    printf("result:%d\n", result);
}

/*
48. 判断能否环绕一圈
同11
*/
void test_can_complete_circuit() {
    std::vector<int> gas = {1,2,3,4,5}; // {2,3,4}; //{1,2,3,4,5};
    std::vector<int> costs = {3,4,5,1,2}; // {3,4,3}; // {3,4,5,1,2};
    // int result = greedy::canCompleteCircuit(gas, costs);
    int result = greedy::canCompleteCircuit_v2(gas, costs);
    printf("results:%d\n", result);
}

/*
49. 正则表达式，类似31
注意初始化匹配0个元素的情况
*/
void test_match_str() {
    std::string s = "aa"; // "adceb";
    std::string p = "*ab"; // "*a*b";
    bool result = greedy::isMatch(s, p);
    printf("result:%d\n", result);
}

/*
50. 删除冗余字符，并使得保留的字符字典序最小
遍历字符串，查询i以后的字符中是否存在该字符
while (result.back()>s[i] && s.find(result.back(), i)!=string::npos) result.pop_back()
*/
void test_remove_duplicate_letters() {
    std::string s = "cbacdcbc"; // "bcabc";
    std:string result = greedy::removeDuplicateLetters(s);
    printf("result:%s\n", result.c_str());
}
/*
51. 求数组中连续子串总和最大的值。
记录curr_sum,如果curr_sum>0 则curr_sum+=nums[i];
else curr_sum=nums[i];
*/
void test_max_sub_array() {
    std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    // int result = dp::maxSubArray(nums);
    int result = dp::maxSubArray_v2(nums);
    printf("result:%d\n", result);
}

/*
52. 求从(0,0)-->(m,n)的路径总和
dp[i][j]=dp[i-1][j]+dp[i][j-1]
*/
void test_unique_path() {
    int result = dp::uniquePaths(7, 3);
    printf("result:%d\n", result);
}
/*
53. 同52
*/
void test_unique_path_with_obstacle() {
    std::vector<std::vector<int>> map = {{0,0,0}, {0,1,0}, {0,0,0}};
    int result = dp::uniquePathsWithObstacles(map);
    printf("result:%d\n", result);
}

/*
54. 求数组中最大的方阵。基于32
从row=0->n即可
*/
void test_max_rectangle() {
    std::vector<std::vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}};
    // int result = dp::maximalRectangle(matrix);
    int result = stack_algs::maximalRectangle(matrix);
    printf("result:%d\n", result);
}

/*
55. 克隆图，类似8.
*/
void test_clone_graph2() {
    graphNode* head = new graphNode(1);
    graphNode* node2 = new graphNode(2);
    graphNode* node3 = new graphNode(3);
    graphNode* node4 = new graphNode(4);
     
    head->neighbors.push_back(node2);
    head->neighbors.push_back(node4);
    node2->neighbors.push_back(head);
    node2->neighbors.push_back(node3);
    node3->neighbors.push_back(node2);
    node3->neighbors.push_back(node4);
    node4->neighbors.push_back(head);
    node4->neighbors.push_back(node3);

    graphNode* copy_head = graph::cloneGraph(head);
    
    std::set<int> visited;
    std::queue<graphNode*> q;
    graphNode* curr = copy_head;
    q.push(curr);
    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if (visited.find(curr->val) != visited.end()) continue;
        visited.insert(curr->val);
        printf("%d: ", curr->val);
        for (int i=0; i<curr->neighbors.size(); i++) {
            printf("%d ", curr->neighbors[i]->val);
            if (visited.find(curr->neighbors[i]->val) == visited.end()) q.push(curr->neighbors[i]);
        }
        printf("\n");
    }
}

/*
56. 判断课程之间的依赖关系，是否可以正常完成课程。即判断拓扑结构中不存在环
队列中保存入度为0的节点，直到遍历完所有节点。
*/
void test_can_finish() {
    std::vector<std::vector<int>>  data = {{0,1}, {0,2}, {1,2}};
    bool result = graph::canFinish(3, data);
    printf("result:%d\n", result);
}

/*
57. 类似56, 保留visit顺序
*/
void test_find_order() {
    std::vector<std::vector<int>>  data = {{0,1}, {0,2}, {1,2}};
    std::vector<int> result = graph::findOrder(3, data);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
58. 将graph转化为树，使其高度最低。
记录每个点的出入度，依次遍历degree=1的点，直到剩下最后1或2个。
*/
void test_find_highest_node() {
    std::vector<std::vector<int>> edges={{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}}; //{{1,0},{1,2},{1,3}};
    std::vector<int> result = graph::findMinHeightTrees(6, edges);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
59. 回溯法生成所有可能结果
*/
void test_letter_combination() {
    std::string digits = "23";
    // std::vector<std::string> result = track_back::letterCombinations(digits);
    std::vector<std::string> result = track_back::letterCombinations_v2(digits);
    for (int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

/*
60. 回溯法生成合法括号：
1. 判断当前字符串中左括号的个数始终>=右括号的个数即合法，其他均不合法。
2. if (left_num>n||right_nst.push(tmp->left);um>n) return;
   if (left_num==n&&right_num==n) collection result;
   if (left_num>=right_num) dfs(curr+'(', left_num+1, right_num, n); dfs(curr+')', left_num, irght_num+1, n);
*/
void test_generate_parenthesis() {
    // std::vector<std::string> result = track_back::generateParenthesis(3);
    std::vector<std::string> result = track_back::generateParenthesis_v2(3);
    for (int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

/*
61. 生成所有sum的结果。
1. 避免重复的组合有点类似三数之和：45， 先对数组sort
2. dfs(combination, curr, index, nums, target)
*/
void test_combination_sum() {
    std::vector<int> candidates = {2,5,2,1,2}; // {10,1,2,7,6,1,5};
    int target = 5; //8;
    std::vector<std::vector<int>> result = track_back::combinationSum2(candidates, target);
    for (int i=0; i<result.size(); i++ ){
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/*
62. 判断二叉树是否正确，即左子树都小于root->val, 又子树大于root->val
dfs(node, low_threshold, high_threshold):
if (node->val >low_threshold && node->val < high_threshold) {
    dfs(node->left, low_threshold, node->val) 
    && dfs(node->right, node->val, high_threshold)
}
再刷感想：1.自底向上判断二叉树是否符合要求．传入low, high两个参数的引用，得到子树的low, high值，然后判断left.high < root->val, right.low > root->val即可．
　　　　　　该方法逻辑稍微有点复杂．
　　　　　2.自顶向下的方法更直观．假设二叉树的range为[low, high], 其左子树若合法，则range必须在[low, root->val], 其右子树若合法，则range必须在[root->val, high]内，
　　　　　　即只需判断if (root->val > low && root->val < high) 即可, 然后判断　左子树，　右子树．

*/
void test_dfs_isvalidtree() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    // root->right->left = new TreeNode(3);
    // root->right->right = new TreeNode(6);
    // bool result = dfs::isValidBST(root);
    bool result = dfs::isValidBST_V2(root);
    printf("result:%d\n", result);
}

/*
63. 从二叉树中找出错位的两个节点，将其交换正常。
1.中序遍历，将其当成一个数组。每次记录上一个节点的val，进行比较。
如果pre->val > curr->val, 则记录pre为第一个错位的点，secod=curr；
再遍历，如果再发现有错位的点，则second=curr，将两者交换即可。
2. 注意dfs， first, second, pre指针使用引用。
*/
void test_recover_tree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    dfs::recoverTree(root);
    TreeNode* curr = root;
    
}

/*
64. 根据中序，先序数组恢复二叉树
递归求解dsf(pre_arr, in_arr, pre_start, pre_end, in_start, in_end)
*/
void test_build_tree() {
    std::vector<int> preorder = {3,9,20,15,7};
    std::vector<int> inorder = {9,3,15,20,7};
    // TreeNode* root = dfs::buildTree(preorder, inorder);
    TreeNode* root = dfs::buildTree_V2(preorder, inorder);
    std::vector<std::vector<int>> result = queue_alg::levelOrder(root);

    std::cout << "test_build_tree result:\n";
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j < result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}

/*
65. 判断一棵二叉树是否对称
对称即左子树等于右子树。
直接对比root与root即可。
isMirror(root1, root2) {
    if (root1==nullptr&&root2==nullptr) return true;
    if (root1==nullptr||root2==nullptr) return false;
    if (root1->val==root2->val) return dfs(root1->left, root2->right) && 
                                       dfs(root1->right, root2->left)
    return false;
}
*/
void test_is_symmetric() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    // bool result = bfs::isSymmetric(root);
    bool result = bfs::isSymmetric_V2(root);
    printf("result:%d\n", result);
}


/*
66. 按层遍历二叉树，按照z字形遍历。
使用队列进行遍历
*/
void test_zigzag_level_order() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    std::vector<std::vector<int>> result = bfs::zigzagLevelOrder(root);
    for (int i=0; i<result.size(); i++) {
        for(int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}


/*
67. 根据wordlist 从start过渡到end
1.先使用queue，bfs判断是否可以过渡到end，并记录path_map[curr].push_back(curr_in)
2.dfs（回溯）根据path_map,从end出发，反向遍历到start。
*/
void test_ladder_length_bfs() {
    std::string start = "red"; // "hit";
    std::string end = "tax"; // "cog";
    std::vector<std::string> wordlist = {"ted","tex","red","tax","tad","rex"}; // {"hot","dot","dog","lot","log","cog"};
    // int step = bfs::ladderLength(start, end, wordlist);
    // printf("result:%d\n", step);
    // std::vector<std::vector<std::string>> result = bfs::findLadders(start, end, wordlist);
    // std::vector<std::vector<std::string>> result = bfs::findLadders_v2(start, end, wordlist);
    std::vector<std::vector<std::string>> result = bfs::findLadders_v3(start, end, wordlist);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%s ", result[i][j].c_str());
        }
        printf("\n");
    }
}

/*
68. 逆波兰式求结果
*/
void test_eval_rpn() {
    std::vector<std::string> tokens = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}; // {"4", "13", "5", "/", "+"}; //{"2", "1", "+", "3", "*"};
    int result = stack_algs::evalRPN(tokens);
    printf("result:%d\n", result);
}

/*
69. 求一段高低不同的洼地，最多能存多少雨水。类似32. 
使用栈维护一个降序队列，当curr_num>stack.top()时，
栈顶元素为下届，当前面积：left = stack.pop().top()（i-left-1）*(min(curr_num, nums[left])-nums[low_idx])
直到栈顶元素大于curr_num或为null。

再刷注意点：1. 使用栈维护降序列表，当height[i]>=height[st.top()]时，计算该凹陷区域的面积．因为计算凹陷区域面积栈里必须有两个元素，要分别判断st是否为空
　　　　　　２．最开始不用单独push 0下标到st中．可以直接整合到for循环中
*/
void test_trap() {
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1}; // {2,1,0,2};
    // int result = stack_algs::trap(height);
    int result = stack_algs::trap_v2(height);
    printf("result:%d\n", result);
}

/*
70. 求第k大的数： 维护一个大小为k的最小堆，或使用快排找mid_indx是否为k，进而调整left，right
1. 构建最小堆，
2. 遍历k->n的数据，如果nums[i]>nums[0]则交换两者，并对堆进行调整
3. 调整堆： while(son<=end) {
    if (son+1<=end && nums[son]>nums[son+1]) son++;
    if (nums[dad]<nums[son]) return;
    swap(nums[dad], nums[son]);
    dad = son;
    son = 2 * dad + 1;
}
*/
void test_find_k_largest() {
    std::vector<int> nums = {3,2,1,5,6,4};; // {7,6,5,4,3,2,1}; //{3,2,1,5,6,4};
    int k = 5; //5; //2;
    // int result = heap::findKthLargest(nums, k);
    int result = heap::findKthLargest_v2(nums, k);
    printf("result:%d\n", result);
}


/*
71. 合并k个list.
递归合并list.
mergelists(vector_list, 0, k)
*/
void test_merge_k_list() {
    std::vector<ListNode*> lists;
    ListNode* root1 = new ListNode(1);
    root1->next = new ListNode(4);
    root1->next->next = new ListNode(5);
    ListNode* root2 = new ListNode(1);
    root2->next = new ListNode(3);
    root2->next->next = new ListNode(4);
    ListNode* root3 = new ListNode(2);
    root3->next = new ListNode(6);
    lists.push_back(root1);
    lists.push_back(root2);
    lists.push_back(root3);
    ListNode* root = heap::mergeKLists(lists);
    while(root!=nullptr) {
        printf("%d ", root->val);
        root = root->next;
    }
    printf("\n");
}

/*
72. 不使用除法完成除法运算。注意数值越界的问题
*/
void test_divide() {
    int dividend = 2147483647; //2147483647;
    int divisor = 1; //3;
    int result = binary_search::divide(dividend, divisor);
    printf("result:%d\n", result);
}

/*
73. 递归寻找旋转数组中是否存在某数。
二分查找，前后两个数组只有一个是乱序的，根据条件判断即可。
*/
void test_search() {
    std::vector<int> nums = {4,5,6,7,0,1,2}; //{3,1}; //{4,5,6,7,0,1,2};
    int target = 4;
    int result = binary_search::search(nums, target);
    printf("result:%d\n", result);
}

/*
74. 从两个排序数组中查找中位数。
使用二分法递归求解, dfs(nums1, low1, nums2, low2, k)
 当k==1时，return min(nums1[low1], nums2[low2])
else{
    if (nums1[low1+k/2-1]<nums2[low2+k/2-1]) return dfs(nums1, low1+k/2, nums2, low2, k-k/2);
    else return dfs(nums1, low1, nums2, low2+k/2, k-k/2);
}
*/
void test_find_median_num() {
    std::vector<int> nums1 = {1,2}; //{1,2}; //{1,3};
    std::vector<int> nums2 = {1,2,3}; //{3,4}; //{2};
    double result = binary_search::findMedianSortedArrays(nums1, nums2);
    printf("result:%f\n", result);
}

/*
75. 将外边界为O的字符的连通区域。
使用stack/queue 递归求解即可
再刷感想：想着dfs从矩阵边界查找＇O'的区域, 将其置为'A'，然后遍历矩阵，其他＇O＇的变成＇X＇, 'A'->'O'即可．
　　　　　其实不用dfs, 直接队列或栈遍历即可．
*/
void test_merge_set() {
    std::vector<std::vector<char>> board={
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    merge_set::solve(board);
    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[0].size(); j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}

/*
76. 判断图中有几个独立连通区域。类似75.
使用栈遍历所有为1的连通区域。不过多加两层for循环并使用visited数组
*/
void test_num_island() {
    // std::vector<std::vector<char>> grid={
    //     {'1', '1', '0', '0', '0'},
    //     {'1', '1', '0', '0', '0'},
    //     {'0', '0', '1', '0', '0'},
    //     {'0', '0', '0', '1', '1'}
    // };
    std::vector<std::vector<char>> grid = {{'1'},{'1'}};
    int result = merge_set::numIslands(grid);
    printf("result:%d\n", result);
}

/*
77. 求出数组中最大连续数字的个数。
1. 使用unordered_set/map.
方法1. 使用set保存数组，遍历nums，求最大连续数
idx = i;while(nums[idx]-1 in set ) idx--; del set[nums[idx]-1]
idx = i+1;while(nums[idx]+1 in set ) idx++; del set[nums[idx]+1]
方法2：
使用并查集。使用map记录每个数字的父节点，以及和该节点属于同一个群的数量。
1.初始化 map[nums[i]]=nums[i], cnt[nums[i]]=1;
for (int i=0;i<n;i++) {
    if (nums[i]+1 in map) {
        result=max(result, mergetwoset(nums[i], nums[i]+1))
    }
}
2. merge two set: 先找出nums[i], nums[i]+1的父节点，
设置nums[i]+1的父节点为nums[i]; cnt[nums[i]]+=cnt[nums[i]+1]
3. 找出父节点的同时更新该群对应点的父节点：
find_root(nums, x): return nums[x]==nums? x: nums[x] = find_root(nums, nums[x]);
*/
void test_longest_consecutive2() {
    std::vector<int> data = {1,2,0,1}; //{100, 4, 200, 1, 3, 2};
    // int result = merge_set::longestConsecutive(data);
    // int result = merge_set::longestConsecutive_v2(data);
    // int result = merge_set::longestConsecutive_V3(data);
    int result = merge_set::longestConsecutive_V4(data);
    printf("result:%d\n", result);
}


/*
78. 将二叉树转化成链表
dfs,中序遍历，伴随一个pre指针
dfs(root,&pre){
    if (root->left！=null) dfs(root->left, pre);
    pre->right=root;
    pre->left=null;
    dfs(root->right, root)
}
*/
void test_bi_node() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(6);
    TreeNode* head = binary_search::convertBiNode(root);
    while(head!=nullptr) {
        printf("%f ", head->val);
        head = head->right;
    }
    printf("\n");
}

/*
79. 删除链表倒数第n个数。
先找到前第n个指针，然后head，nnode指针依次遍历，当nnode指针到最后时，head指针刚好是倒数第n的位置。
*/
void test_remove_nth_node() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* new_head = listnode_alg::removeNthFromEnd(head, 2);
    while(new_head!=nullptr) {
        printf("%d ", new_head->val);
        new_head = new_head->next;
    }
    printf("\n");
}
/*
80. 求不包含重复字符的最长子串。
使用滑窗。unordered_set保存当前窗口的内容。如果窗口中已经存在s[i]，
则一直递增left，删除窗口内容，直到窗口中不存在s[i].
注意最后需要把s[i]加入到窗口中
*/
void test_length_substr() {
    std::string str = "pwwkew";
    // int result = binary_pointer::lengthOfLongestSubstring(str);
    // int result = binary_pointer::lengthOfLongestSubstring_v2(str);
    int result = binary_pointer::lengthOfLongestSubstring_v3(str);
    printf("result:%d\n", result);
}

void test_unordered_map() {
    std::unordered_map<int ,int> map = {{1,1},{2,2}};
    map.insert({3,3});
    for (std::pair<int ,int> pair: map) {
        printf("%d: %d\n", pair.first, pair.second);
    }
    for (std::unordered_map<int,int>::iterator iter=map.begin(); iter!=map.end(); iter++) {
        printf("%d: %d\n", (*iter).first, (*iter).second);
    }
}

/* 
81. 求二叉树中每个节点>=其值的和
递归遍历求和，先遍历: right, root, left. 记录一个pre节点，每个节点val=pre->val + val;
*/
void test_dfs_bstTogst() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(1);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    root->right->right->right = new TreeNode(8);

    TreeNode* new_root = binary_search::bstToGst(root);
    TreeNode* curr = new_root;
    std::queue<TreeNode*> q;
    q.push(curr);
    while(!q.empty()) {
        TreeNode* tmp = q.front(); q.pop();
        printf("%f ", tmp->val);
        if (tmp->left!=nullptr) q.push(tmp->left);
        if (tmp->right!=nullptr) q.push(tmp->right);
    }
    printf("\n");
}

/*
82. 将链表每隔k个节点反序列
1.注意传入函数的指针已经被修改．
2.reverse listnode ：反序一个list, 从pre->next到end. 其返回反序后的列表的最后一个节点．因为最后一个节点的next指针需要额外设置．
*/
void test_swap_pair() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // ListNode* new_head = listnode_alg::swapPairs(head);
    ListNode* new_head = listnode_alg::reverseKGroup(head, 3);
    while(new_head!=nullptr) {
        printf("%d ", new_head->val);
        new_head = new_head->next;
    }
    printf("\n");
}

/*
83. 记录S中包含T所有字符的最小子串。
滑窗原理。主要T中可能存在重复字符。
再刷感想：1. 根据unique_cnt==0的时候左滑窗口，注意left已经过了起始点了，开始的节点应该在left-1
        2. 要记录最小len情况下left的下标，　而不是curr_left会一直到最后．
*/
void test_min_window() {
    std::string s = "ADOBECODEBANC"; //"aa"; //"ADOBECODEBANC";
    std::string t = "ABC"; //"a"; //"ABC";
    // std::string result = binary_pointer::minWindow(s, t);
    // std::string result = binary_pointer::minWindow_v2(s, t);
    std::string result = binary_pointer::minWindow_v3(s, t);
    printf("result:%s\n", result.c_str());
}

/*
84. 找出S中包含所有words的起始位置。
1. 滑窗原理．因为words固定长度，但不知道开始的index在哪，故外层循环遍历i=0->word_len, 内层训练即可依次遍历　i+word_len, i + 2 * word_len进行滑窗．
2. 恰好匹配，中间不能存在其他字符。也可使用滑窗用map记录words是否匹配。
只要在匹配后再判断right-left+1==len(words)*word_len即可。
*/
void test_find_substr() {
    std::string s = "foobarthefoobarman"; //"wordgoodgoodgoodbestword"; // "wordgoodgoodgoodbestword";
    std::vector<std::string> words = {"bar","foo"}; //{"word","good","best","good"}; // {"word","good","best","word"};
    // std::vector<int> result = binary_pointer::findSubstring(s, words);
    std::vector<int> result = binary_pointer::findSubstring_v2(s, words);
    for (int i=0; i<result.size(); i++)
        printf("%d ", result[i]);
    printf("\n");
}

/*
85. 找出最长有效括号子串的长度
注意连续的有效括号。
1.使用栈遍历。len[i]表示以i结尾的有效括号个数。
则如果s[i]==')', stack.pop(),len[i]=i-stack.top()+1+len[stack.top()-1]
2. 也可以使用栈来标记，即匹配有效括号后，
如果栈顶为空，说明前面所有字符都是正确的括号，则len=i
如果栈顶不为空，则 len=i-stack.top()

******************
再刷: 这种括号匹配的用栈，左括号对应下标入栈，右括号则出栈，求出curr_idx - left_idx +1　即为当前匹配的长度，同时，加上前面匹配的长度len[left_idx-1]
再刷感想：返回结果时，不是直接返回dp[n-1], 应该有个result变量记录最长的长度．

*/
void test_longest_valid_parentheses() {
    std::string s = ")()())"; //"(()"; //"()()()";
    // int result = stack_algs::longestValidParentheses(s);
    // int result = stack_algs::longestValidParentheses_v2(s);
    // int result = stack_algs::longestValidParentheses_v3(s);
    int result = stack_algs::longestValidParentheses_v4(s);
    printf("result:%d\n", result);
}

/*
86. 模拟乘法。
1. 逐位乘法，result[i+j] +=nums[i]*nums[j]%10;rseult[i+j+1] += nums[i]*nums[j]/10;
2. 经过1后，result也会存在>10的数，做完乘法后要再做一遍除余。
*/
void test_multiply() {
    std::string num1 = "123";
    std::string num2 = "456";
    std::string result = str_alg::multiply(num1, num2);
    printf("result:%s\n", result.c_str());
}

/*
87. 求矩阵中最长的连续递增串
将连续递增的关系表示为有向图，得到每个点的in_degrees[m][n], 将所有入度为０的点push到queue中，直到queue为空．
*/
void test_longest_increaseing_path() {
    std::vector<std::vector<int>> matrix = {{3,4,5},{3,2,6},{2,2,1}}; // {{9,9,4},{6,6,8},{2,1,1}};
    int result = topoloical_sort::longestIncreasingPath(matrix);
    printf("result:%d\n", result);
}

/*
88. 从shorter, longer中选取k个数，求所有可能出现的和
*/
void test_diving_board() {
    int shorter = 1;
    int longer = 1;
    int k = 0;
    std::vector<int> result = memory_alg::divingBoard(shorter, longer, k);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
89. 将字符串拆分，得到未匹配的字符个数
dp[i]表示0->1的字符串中未匹配的个数．则 从0遍历ｊ到ｉ, 如果str(j, i) in dict, dp[i]=  min(dp[i-1]+1, dp[j-1]) 否则　dp[i] = dp[i-1] +1;
*/
void test_respace() {
    std::vector<std::string> dict = {"looked","just","like","her","brother"};
    std::string sentence = "jesslookedjustliketimherbrother";
    int result = memory_alg::respace(dict, sentence);
    printf("result:%d\n", result);
}


/*
90. 给定target，判断数组中是否存在两数之和为target.
hash map求解，要注意重复元素的问题
*/
void test_two_sum() {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = hash_alg::twoSum(nums, target);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}


/*
91. 给定数组，求４数之和的可能结果，　解法和45.三数之和一样．
先对nums排序，两重for循环，里面两个指针依次递增或递减．
要注意四个指针的范围，每个指针避免使用重复元素．
*/
void test_foursum() {
    std::vector<int>  nums = {-1,2,2,-5,0,-1,4}; // {-1,0,-5,-2,-2,-4,0,1,-2}; // {0,0,0,0}; // {1, 0, -1, 0, -2, 2};
    int target = 3; // -9; //0;
    std::vector<std::vector<int>> result = hash_alg::fourSum(nums, target);
    for (int i=0 ;i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/*
92. 返回数组中所有可能的子集
1. 回溯法，dsf(combinations, curr, nums, idx); 其中为了避免访问重复元素，以及数字顺序不同的组合．必须使idx必须为当前加入curr的下一个位置
for (int i=idx; i<nums.size(); i++) {
    curr.push_back(nums[i]);
    combinations.push_back(curr);
    dfs(combinations, curr, nums, i+1);
}

2. 用比特位表示第ｉ个数字是否出现. n个数字，一共２^n次方种可能．
total_count = 1<<n;
for (int i=0; i<total_count; i++) {
    curr;
    int tmp=i;
    for (int j=0; j<n;j++) if (tmp&1==1) curr.push_back(nums[j]);
    tmp=tmp>>1;
    result.push_bakc(curr);
}
*/
void test_subsets() {
    std::vector<int> nums = {1,2,3};
    // std::vector<std::vector<int>> result = bits_alg::subsets(nums);
    // std::vector<std::vector<int>> result = bits_alg::subsets_v2(nums);
    std::vector<std::vector<int>> result = track_back::subsets(nums);
    for (int i=0; i<result.size(); i++) {
        printf("%d:", i);
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/*
92. 找出字符串中出现超过１次的长度超过或等于１０个字符的子串
１．从ｉ=0->n-9; 判断sub 是否在map中，如果在则重复出现，否则将新字符串放入map, 注意避免重复加入相同子串．
２．使用比特位维护１０个位置的字符标志，如A:0, C;1, G:2, T:3, 则长度为１０的字符串，需要用２０比特位即可表示．
初始化构建前９个比特位的数值：　for(i=0; i<9; i++) curr = curr<<2; curr = curr| char2num[s[i]]
遍历剩下字符串：　for(i=9; i<n;i++) curr = curr<<2; curr = curr|char2nums[s[i]]; curr = curr & 0x000fffff;
if (map.find(curr)!=map.end()) map[curr]++; if (map[curr]==2) result.push_back(substr);
else map[pcurr] =1;
*/
void test_find_repeated_dnasequence() {
    std::string s = "AAAAAAAAAAAA"; //"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    std::vector<std::string> result = bits_alg::findRepeatedDnaSequences(s);
    for (int i=0 ;i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

/*
93. LRU 实现, 要求查找，插入均为O(1), 使用hash map+双向链表．
１．双向链表用于从头插入，从尾部删除，同时为了映射回map, 双向链表应该保留key, val.
2. hash map用于查找，key--> 对应节点指针．可使用ｕnordered_map + list　实现．注意　不能使用ｖector作为list，
因为ｖector会自动扩展空间，并把原始数据复制到新空间去，对于map中记录对于指针的话，map中原始指针会失效．
*/
void test_lru() {
    // design_alg::LRUCache* obj = new design_alg::LRUCache(2);
    // design_alg::LRUCache_v2* obj = new design_alg::LRUCache_v2(2);
    design_alg::LRUCache_v3* obj = new design_alg::LRUCache_v3(2);
    obj->put(1,1);
    obj->put(2,2);
    int val1 = obj->get(1);
    obj->put(3, 3);
    int val2 = obj->get(2);
    obj->put(4, 4);
    int val3 = obj->get(1);
    int val4 = obj->get(3);
    int val5 = obj->get(4);
}

/*
94. 桶排序, 求出未排序数组中排序后数字最大间隔的值，　要求O(n)
１．　简单做法类似这种未排序数组，求间距的题目应该想到map, 将值映射到map中作为key. 
2. 桶排序，
桶间距 = 区间长度 / (ｎ个数字划分出的区间个数)
加１解决最大值的区间问题．　如nums=[2,4,6,8], gap=2, 不加１，　bucket_num=3, bucket_nums的下标=[0,1,2], 
则最大值8映射bucket id时等于(8-2)/bucket_num=3, 不在bucket nums下标中，故多加一个bucket即可．其其实是解决开闭区间的问题：［2, 4), ［4, 6), ［6, 8)
*/
void test_maximum_gap() {
    std::vector<int> nums = {1, 5, 2, 9};
    // int result = sort::maximumGap(nums);
    // int result = sort::maximumGap_v2(nums);
    // int result = sort::maximumGap_repeated(nums);
    int result = sort::maximumGap_v2_repeated(nums);

    printf("result: %d\n", result);
}

/**
 * 94. 用队列实现栈．
 * 在pop的时候，依次pop/push前n-1个数，pop最后一个数则为栈顶元素
*/
void test_mystack() {
    design_alg::MyStack* obj = new design_alg::MyStack();
    obj->push(1);
    int param_2 = obj->pop();
    int param_3 = obj->top();
    bool param_4 = obj->empty();
}

/**
 * 95. 实现Trie前缀树　类定义的变量有: Trie* tries[26] 字母a-z的映射，　isEnd判断该点是否为单词的末尾．
 * 主要在insert的时候要判断tries[word[i]-'a']是否为null, 不为null，则直接往下走，为空则new tire 
*/
void test_trie() {
    design_alg::Trie* obj = new design_alg::Trie();
    std::string word = "abc";
    std::string prefix = "ab";
    obj->insert(word);
    bool param_2 = obj->search(word);
    bool param_3 = obj->startsWith(prefix);
    bool param_4 = obj->word_dictionary_search("a.a");
    printf("param_2:%d, param_3:%d, param_4:%d\n", param_2, param_3, param_4);
}

/**
 * 96. 从board中查找words中存在的单词．Trie tree + 回溯．
 * 要注意visited
 * 
*/
void test_findword() {
    std::vector<std::vector<char>> boards = {{'o','a','a','n'}, {'e','t','a','e'}, {'i','h','k','r'}, {'i','f','l','v'}};
    std::vector<std::string> words = {"oath", "pea", "eat", "rain"};
    // std::vector<std::string> result = dict_tree_alg::findWords(boards, words);
    std::vector<std::string> result = dict_tree_alg::findWords_v2(boards, words);
    for (int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

/**
 * 97. 画出天际线：　用线段树．
 * １．先对所有的点进行排序<x, height>,　其中开始节点的height为负数．排序后的节点按照横坐标递增．
 * ２．遍历排序后的点，如果为开始节点则将高度放入最大堆中，结束点则将该高度删除．
 * ３．得到当前堆中最大高度，如果当前最大高度和先前最大高度不同，则该点是关键点．
*/
void test_get_skyline() {
    std::vector<std::vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}}; // {{0,1,3}};
    std::vector<std::vector<int>> result = line_tree_alg::getSkyline(buildings);
    for (int i=0; i<result.size(); i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }
}

/**
 * 98. 线段树求和. 两种方法：１．树状数组．　２．线段树
 * １．　树状数组．sum[i]存放的是sum(i) + sum(i-lowbit(i))的结果，直到ｉ变为０
 * sum[0+1]=sum(0), sum[1+1]=sum(0->1), 
 * sum[2+1]=sum(2), sum[3+1] = sum(0->3)
 * 则更新第ｉ个值为value时，其只会影响sum(i), sum(i+lowbit(i))的值，直到ｉ>n,;
 * 求i,j区间的和时，为sum(0->j)-sum（０－ｉ）, sum(0->j)= sum（j）+sum(j-=lowbit((j)), 直到j=0;
 * 注意在初始化sum数组时，sum[i] = pre_sum[i]-pre_sum[i-lowbit[i]]; 如sum[5]=pre[5]-pre[4]; sum[6]=pre[6]-pre[4];
 * 2. 线段树. SegNode{sum, begin, end, SegNode* left, SegNode* right} 在更新idx值时，当root->begin==root->right, root->sum=val; 
 * 否则mid=(root->begin+root->end)/2; if (idx<=mid) update(root->left, idx, val); else(root->right, idx, val)
 * 在查询求和时，if (root->begin==root->end) return root->sum 
 * 否则计算当前线段树的中间点，若求和范围left小于等于中间点，则计算左子树中left,right范围的和，若求和范围right大于中间点，再计算右子树中left,right范围的和．
 * 注意：　１．初始化线段树时，更新树的begin/end值．　２. 更新的if/else 条件可以并列; 但求和的两个if条件必须分别判断．
*/
void test_numarray() {
    std::vector<int> nums = {0,9,5,7,3}; // {1,3,5}; //{7,2,7,2,0}; //{}; //{1,3,5};
    // line_tree_alg::NumArray* obj = new line_tree_alg::NumArray(nums);
    // line_tree_alg::NumArray_v2* obj = new line_tree_alg::NumArray_v2(nums);
    line_tree_alg::NumArray_v3* obj = new line_tree_alg::NumArray_v3(nums);
    int param_0 = obj->sumRange(4,4);
    int param_1 = obj->sumRange(2,4);
    obj->update(1,2);
    int param_2 = obj->sumRange(0,2);
    printf("param1:%d, params2:%d\n", param_1, param_2);
    // obj->update(4,6);
    // obj->update(0,2);
    // obj->update(0,9);
    // int sum1 = obj->sumRange(4,4);
    // obj->update(3,8);
    // int sum2 = obj->sumRange(0,4);
    // printf("sum1:%d, sum2:%d\n", sum1, sum2);
}

/**
 * 99. 求未排序数组的逆序对．
 * 1. 使用归并排序，在对各自排好序的nums1,nums2求逆序对，然后再对num1, num2进行merge.　其中num1所有元素均小于num2;
*/
void test_reverse_pairs() {
    std::vector<int> nums = {1,3,2,3,1}; //{2,4,3,5,1}; // {1,3,2,3,1};
    // int result = sort::merge_sort_reverse_pair(nums, 0, nums.size()-1);
    int result = line_tree_alg::reversePairs(nums);
    printf("result:%d\n", result);
}
/**
 * 100. 判断先手是否能赢, 找规律当n是４的倍数的时候，会输，其他情况会赢．如n=4的时候，无论拿１，２，３，后手都会全部拿走．n=5时，先手拿1,后手无论拿几都会留一个．
 * ２.dp思路．　假设dp[ｉ]表示ｉ个数时，先手的输赢状态，则dp[i]等于true的条件为，dp[i-3],dp[i-2],dp[i-1]中有一个是输，
 * 即dp[i]=!(dp[i-3]&dp[i-2]&dp[i-1])
 * 
*/
void test_can_win_nim() {
    bool result = minimization_alg::canWinNim(7);
    printf("result:%d\n", result);
}

/**
 * 101. 猜数字. 求完成游戏需要的最小数值, dp方法，dp[i][j]表示完成i->j的猜字游戏需要的money．则dp[i][j]至少需要　for k=i->j, min(k + max(dp[i][k-1], dp[k+1][j])),
 * 里面的max表示设定的数字可能在左边，也可能在右边，所以取最大值．
*/
void test_get_menoy_account() {
    int result = minimization_alg::getMoneyAmount(10);
    printf("result:%d\n", result);
}

/**
 * 102. 随机选取链表中的数，保证每个节点被选取的概率相同. 依次遍历链表．并记录已遍历的节点个数count．
 * 当遍历到ｉ点时，　当前节点有1/i的概率被选择，保留之前的数的概率为（ｉ－１）／ｉ.则每个节点最后被选择的概率为1/n, 
 * 如n=4, 1被选择的概率=1/1 * (2-1)/2 *(3-1)/3*(4-1)/4 = 1/4
 * 
*/
void test_random_sample() {
    ListNode* root = new ListNode(1);
    root->next = new ListNode(2);
    root->next->next = new ListNode(3);
    random_sample_alg::Solution* obj = new random_sample_alg::Solution(root);
    int result = obj->getRandom();
    printf("result: %d\n", result);
    result = obj->getRandom();
    printf("result 2: %d\n", result);
    result = obj->getRandom();
    printf("result 3: %d\n", result);
}

/**
 * 103. 从存在重复元素的数组中选取对应数值的下标，　存在多个下标则随机返回任意一个下标．
 * 同102, 记录target的个数，当前target被选择的概率为1/count
*/
void test_pick_target() {
    std::vector<int> nums = {1,2,1,2,3,5};
    int result = random_sample_alg::pick_idx(nums, 2);
    printf("result:%d\n", result);
}

/**
 * 104. 求物体表面积, 每个方格的表面积＝上下底面＋四周面积，其中四周面积当周围高度比他高时，该面没有表面积
*/
void test_surface_area() {
    std::vector<std::vector<int>> grid = {{1,2}, {3,4}}; //{{2}};
    int result = geometric_alg::surfaceArea(grid);
    printf("result:%d\n", result);
}

/**
 * 105. 求所给出的点是否共线．要先排除重合点，水平，垂直线的可能．正常斜率下用最大公约数求得斜率的向量表示．
*/
void test_check_straightline() {
    std::vector<std::vector<int>>  coordinates = {{1,1},{2,2},{3,4},{4,5},{5,6},{7,7}};
    bool result = geometric_alg::checkStraightLine(coordinates);
    printf("result:%d\n", result);
}

/**
 * 106. 访问所有点需要的最短距离
*/
void test_min_time_visitedall() {
    std::vector<std::vector<int>> points = {{1,1},{3,4},{-1,0}};
    int result = geometric_alg::minTimeToVisitAllPoints(points);
    printf("result:%d\n", result);
}

/**
 * 107. 求两条线段是否共线．求两个线段的公共区域时，并不能分别根据两个线段的start, end求公共区域，这样会忽略斜率为负数的情况，
 * 1. 应该对每条线段的x,y求min,max, 以此为区间，再根据两条线段的min中取max, max中取min
 * 2. 注意各种边界条件．
*/
void test_inter_section() {
    std::vector<std::vector<int>> points = {{0, 0}, {1, 0}, {1, 1}, {0, -1}}; //{{0, 0}, {1, -1}, {0, 0}, {-1, 1}}; //{{0, 0}, {3, 3}, {1, 1}, {2, 2}}; //{{0, 0}, {1, 0}, {1, 1}, {0, -1}};
    std::vector<double> result = geometric_alg::intersection(points[0], points[1], points[2], points[3]);
    printf("result:");
    for (int i=0; i<result.size(); i++) {
        printf("%lf ", result[i]);
    }
    printf("\n");
}

/**
 * 108. 求二叉树路径最大和. dfs, 注意全局变量保存最大path sum, 而dfs返回包含当前节点的单个最大path.
 * 当节点为null, 直接返回０，　通过max(0, val)可以去除很多判断；
 * max_path = root->val +max(0, max(left_max, right_max));
 * curr = max(curr, root->val+max(0, left_max) + max(0, right_max))
*/

void test_max_sum_path() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(-1);
    // root->right = new TreeNode(3);
    // TreeNode* root = new TreeNode(-10);
    // root->left = new TreeNode(9);
    // root->right = new TreeNode(20);
    // root->right->left = new TreeNode(15);
    // root->right->right = new TreeNode(7);
    int result = binary_search::maxPathSum(root);
    printf("result:%d\n", result);
}

/**
 * 109. 求数组中连续元素和为target的组合数．
 * 1. 使用滑窗原理, 当剩余target>0, 一直往前，　<=0后，　left往前．这种只适用于target, nums均为正数的情况，　负数情况下不适用．
 * ２．记录前缀和，k,v 分别表示前缀和为k,在0->当前index情况下出现了ｖ次，遍历数组，　当map中存在sum-target时，则表示存在为target的连续子序列，cnt+=map[sum-target], 注意相同值的前缀和可能出现多次．
*/
void test_sub_array_sum() {
    std::vector<int> arr = {28, 54, 7, -70, 22, 65, -6}; //{-1,-1,1};
    int result = binary_pointer::subarraySum(arr, 100);
    printf("result:%d\n", result);
}

/**
 * 110. 排序数组中找特定target, 二分法，找到一个idx, 然后向两边扩散
*/
void test_search_range() {
    std::vector<int> nums = {5, 7, 7, 8, 8, 10};
    // std::vector<int> result = binary_search::searchRange(nums, 8);
    std::vector<int> result = binary_search::searchRange_v2(nums, 9);
    printf("result left:%d, right:%d\n", result[0], result[1]);
}

/**
 * 111. 循环队列实现。要区分队列空，满两种状态，
 * 1. front == rear 为空，(front+1) % 10 == rear 为满；
 * 2. push时，push到front后，在front+1， 而不是push到front+1的位置。front表示当前空闲的位置。
 * 3. 1中两者状态，区分。如size=5， front=rear=0, 当push 4个数据后，
 * front=4, (front+1)%5==rear, 则此时queue已满。当pop一个元素后，则可push到idx=4的位置，
 * 只要保证front与rear有一个间隔即可。
*/
void test_queue() {
    CircularQueue q = CircularQueue(10);
    q.push(1);
    q.push(2);
    int result = q.pop();
    printf("result:%d\n", result);
}

/**
 * 112. 生成全排列，　回溯+dfs
*/
void test_permute() {
    std::vector<int> nums = {1, 2, 3};
    std::vector<std::vector<int>> result = bfs::permute(nums);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/**
 * 113. 生成下一个排列.思路：1. 从后往前遍历，如果存在a[i-1]<a[i]的情况，则存在下一个递增排列。
 * 记录idx=i-1的位置，然后从idx+1->nums.size()找到比nums[idx]大，且最小的数，
 * swap，然后sort idx+1->end这段
 * 2. 其实idx后面的数都是递减排列的，swap其中大于nums[idx]后其顺序还是递减的，所以直接reverse即可。
*/
void test_next_permute() {
    std::vector<int> nums = {5,2,1,4,7,6,3};
    bfs::nextPermutation(nums);
    for (int i=0; i<nums.size(); i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

/**
 * 113. 生成总和为sum的所有可能组合. 因为可以重复使用，所以dfs中下标从idx开始，而不是idx+1
 *　
*/
void test_combinationsum() {
    std::vector<int> candidates = {2,3,5}; //{2,3,6,7};
    int target = 8; //7;
    std::vector<std::vector<int>> result = bfs::combinationSum(candidates, target);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

/**
 * 114.　升序的二维数组排列．因为该二维数组前一行最后一个数一定小于该行第一个数，所以整个二维数组是完全升序的，直接按照一维数组二分查找即可，只不过把一维数组下标映射到二维数组中即可．
*/
void test_searchmatrix() {
    std::vector<std::vector<int>> matrix = {{1,1}}; //{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
    int target = 2; //13;
    bool result = binary_search::searchMatrix(matrix, target);
    printf("result: %d\n",  result);
}

/**
 * 115. 二维矩阵中寻找第ｋ小的数．　刚开始的想法是求得第小ｋ元素所在行数，即sqrt(k), 则第ｋ小肯定在arr[idx][0-idx]或arr[0-idx][idx]之间．其实不是．
 * 如下面数组，k=3时，idx=1, 第３小的数应该在matrix[1][0-1], matrix[0-1][1]之间，但真实结果在marix[0][2].
 * 解题思路: 1. 得到数组最小，最大值left, right. 2. 每次都计算二维数组中<=mid的个数cnt，当cnt < k, 则left=mid+1; 否则right=mid;循环直到left==right, 则第ｋ小的值为left;
 * 2. 其中注意　不能添加if(cnt==k) return mid, else right=mid-1的条件，　因为cnt==k,只说明第ｋｉ小的数在left-->mid之间，而不是mid. 
 * 3. 在求得二维数组中小于等于ｖal的个数中，一列的方式求，i=row, j=0; 如果arr[i][0]<val,则说明该列均小于ｖal, cnt+=i+1; 否则　ｉ--;
*/
void test_kthsmallest() {
    std::vector<std::vector<int>>  matrix = {{1, 3, 5}, {10, 11, 16}, {23, 30, 34}};
    int k = 5;
    int result = binary_search::kthSmallest(matrix, k);
    printf("result: %d\n", result);
}

/**
 * 116. 在不开辟新空间情况下将数组旋转90度. 
 * 主要推导出四个点的相对位置．(i, j) --> (j, n-i-1) --> (n-i-1, n-j-1) --> (n-j-1, i)
 * 便于推导：(1)第ｉ行j列的数，旋转的位置的列数为n-i-1, 行数为j; (2) 第三个点关于第一个点中心对称，即（n-i-1, n-j-1）; (3)第四个点关于第二个点中心对称．
 * 注意若行数为单数，最后一个环只有１个元素，不需要转换
 * 再刷，注意ｉ点：1.注意两层for循环的起始，结束位置．　外层循环应该以环数为主，即0->n/2; 内层循环下标从ｉ－＞n-i-1
*/
void test_rotate_matrix() {
    std::vector<std::vector<int>> matrix = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};; //{{1,2,3}, {4,5,6}, {7,8,9}};
    // search::rotate(matrix);
    search::rotate_v2(matrix);
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * 117. 划分字母相同，排列不同的字符串, 1. 对每个单词都sort, 如果sort后的词相同，则相同；
 * 2. 用map<char, int>　记录一个单词的信息，　map<map<char, int>, vector<string>> 作为map. 
 * 这里不能用unordered_map, 只能用map. 因为unordered_map内部实现是std::hash,而pair或unorodered_map<char, int>等这种双值的类型c++ library中没有对应的hash functor, 故报错．
 * 而std::map的内部实现是红黑树，对key的类型没有要求，故这里使用std::map. map内部本身有序，适合对顺序有要求的场景，而unordered_map适合于查找．
*/
void test_groupAnagrams() {
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    // std::vector<std::vector<std::string>> result = search::groupAnagrams(strs);
    std::vector<std::vector<std::string>> result = search::groupAnagrams_v2(strs);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%s ", result[i][j].c_str());
        }
        printf("\n");
    }
}

/**
 * 118. 寻找二叉树中下一个节点. 当节点存在right节点时，下一个节点为right; 否则寻找父节点．　当该节点为父节点的左子树，则下一个节点为该父节点；否则一直网上寻找父节点．直到该节点为父节点的左子树为止．
*/
void test_next_node() {
    TreeLinkNode* root = new TreeLinkNode(0);
    root->left = new TreeLinkNode(1);
    root->left->next = root;
    root->right = new TreeLinkNode(2);
    root->right->next = root;

    root->left->left = new TreeLinkNode(3);
    root->left->right = new TreeLinkNode(4);
    root->left->left->next = root->left;
    root->left->right->next = root->left;

    root->right->left = new TreeLinkNode(5);
    root->right->left->next = root->right;

    TreeLinkNode* next = binary_search::next_node(root->right);
    if (next != nullptr)
        printf("next node: %d\n", next->val);
    else printf("curr node is in the end!\n");
    // next = binary_search::next_node(root->left);
    // printf("next node: %d\n", next->val);
    // next = binary_search::next_node(root->left->right);
    // printf("next node: %d\n", next->val);
}

/**
 * 119. 用栈实现队列. 注意pop的时候，只有当s2为空时才从s1中将所有item　pop出来．
*/
void test_myqueue() {
    design_alg::MyQueue q = design_alg::MyQueue();
    q.push(1);
    q.push(2);
    int tmp = q.pop();
    printf("%d \n", tmp);
    q.push(3);
    tmp = q.pop();
    printf("%d \n", tmp);
    tmp = q.pop();
    printf("%d \n", tmp);
    tmp = q.pop();
    printf("%d \n", tmp);
}

/**
 * 120. 打印１->ｎ位最大数
*/

void test_print1ToNdigits() {
    // sword_finger_offer::print1ToMaxNDigits(1);
    sword_finger_offer::print1ToMaxNDigits_v2(2);
}

/**
 * 121. 删除链表中重复节点
*/
void test_deleteduplictednode() {
    ListNode* root = new ListNode(1);
    root->next = new ListNode(1);
    root->next->next = new ListNode(2);
    root->next->next->next = new ListNode(3);
    root->next->next->next->next = new ListNode(3);
    // ListNode* root = nullptr;
    sword_finger_offer::deleteDuplicatedNode(&root);
    ListNode* curr = root;
    while (curr != nullptr)
    {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

/**
 * 122. 正则表达式，类似与４９，３１，　递归实现．
*/
void test_regular_match_v2() {
    std::string str = "aaa";
    std::string pattern = "ab*ac*a*";
    bool result = sword_finger_offer::regular_pattern(str, pattern);
    std::cout << "result: " << std::boolalpha << result << std::endl;
}

/**
 * 123. 判断字符是否为有效数字．将有效数字拆分成A[.B][e|EC], .B[e|EC]的形式, 其中A, C为整数，　Ｂ为正整数. 
 * 1. 注意判断当前字符串为整数应该是s[i]=='.'||s[i]=='e'||s[i]==='E' 且i>0
 * 2. A/B二者存在其中一个就行．即判断条件为scanUnsignedInteger(s, index) || isnumeric,　且必须scanUnsignedInteger放前面，否则isnumeric为true,则不只是scanunsiged函数
*/
void test_isNumeric() {
    std::vector<std::string> cases = {"e+5", "+100", "-1e-12", "3.146", "12e+5.4", "12.e5", ".1e-5"};
    for (auto& str: cases) {
        bool result = sword_finger_offer::isNumeric(str);
        std::cout << "result of: " << str << " is " << std::boolalpha << result << std::endl;
    }
}

/**
 * 124. 抽象判断条件，划分数组，设置奇偶数
*/
void test_reordervec() {
    std::vector<int> vec{5,4,1,2,3,4};
    auto isodd = [](int val)->bool {return (val & 0x1) == 1;};
    sword_finger_offer::reorderVec(vec, isodd);
    for (int i=0; i<vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 125. 判断链表中是否存在环
*/
void test_detect_cycle(){
    ListNode* root = new ListNode(1);
    ListNode* tmp = root;
    tmp->next = new ListNode(2);
    tmp = tmp->next;
    tmp->next = new ListNode(3);
    tmp = tmp->next;
    tmp->next = new ListNode(4);
    tmp = tmp->next;
    tmp->next = new ListNode(5);
    tmp = tmp->next;
    tmp->next = root->next;
    ListNode* src = root;
    ListNode* result = sword_finger_offer::detectCycle(root);
    if (result != nullptr)
        std::cout << "ring begining value: " << result->val << std::endl;
    else
        std::cout << "the listnode has no ring\n";
}

/**
 * 126. 反转链表，　额外添加一个头指针，可去除判断头指针特殊情况．注意删除额外的头指针
*/
void test_reverse_list() {
    ListNode* root = new ListNode(1);
    ListNode* tmp = root;
    tmp->next = new ListNode(2);
    tmp = tmp->next;
    tmp->next = new ListNode(3);
    tmp = tmp->next;
    tmp->next = new ListNode(4);
    tmp = tmp->next;
    tmp->next = new ListNode(5);

    ListNode* head = sword_finger_offer::reverseList(root);

    std::cout << "reversed list: " ;
    while(head !=nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

/**
 * 127. 合并两个排序链表. 使用dfs方法实现:输入为两个头节点，　返回值为合并链表的头节点．
 * 根据root1,root2的ｖal大小，确定当前head=root1 或root2, head->next = merge(root1->next, root2) 或merge(root1, root2->next);
*/
void test_merge_two_list() {
    ListNode* root1 = new ListNode(1);
    ListNode* tmp = root1;
    tmp->next = new ListNode(2);
    tmp = tmp->next;
    tmp->next = new ListNode(3);

    ListNode* root2 = new ListNode(4);
    tmp = root2;
    // tmp->next = new ListNode(5);
    // tmp = tmp->next;
    // tmp->next = new ListNode(6);


    // ListNode* mergeList = sword_finger_offer::mergetwoList(root1, root2);
    ListNode* mergeList = sword_finger_offer::mergetwoList_v2(root1, root2);

    std::cout << "the two merged list: ";
    while(mergeList != nullptr) {
        std::cout << mergeList->val << " ";
        mergeList = mergeList->next;
    }
    std::cout << std::endl;
}

/**
 * 128. 判断是否为子树
*/
void test_issubtree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->right->left = new TreeNode(2);
    // root->left->left = new TreeNode(0);
    TreeNode* sub = new TreeNode(3);
    // sub->left = new TreeNode(4);
    sub->right = new TreeNode(5);
    bool result = sword_finger_offer::issubtree(root, sub);
    std::cout << "is sub tree: " << std::boolalpha << result << std::endl;
}

/**
 * 129. 判断二叉树是否对称，　即判断二叉树的左子树是否等于右子树．　为了使得左子树与对应右子树匹配．定义输入为两颗二叉树的对比函数，比较二叉树与其自身是否对称．
*/
void test_issymmetrical() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(4);
    root->left->left = new TreeNode(1);
    // root->left->right = new TreeNode(2);
    // root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(1);
    bool result = sword_finger_offer::isSymmetrical(root);
    std::cout << "is symmetrical tree: " << std::boolalpha << result << std::endl;
}

/**
 * 130. 顺时针打印矩阵，　同42
*/
void test_clockwise_print() {
    std::vector<std::vector<int>> matrix = {{1,2,3}, {5,6,7}, {9,10,11}, {13,14,15}}; // {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}}; // {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}}; // {{1,2,3}, {4,5,6}, {7,8,9}};
    sword_finger_offer::clockwise_print(matrix);

}

/**
 * 131. 包含min函数的栈
*/
void test_min_stack() {
    sword_finger_offer::minStack<int> s;
    int result=-1;
    s.push(5);
    s.push(2);
    bool flag = s.min(result);
    if (flag) std::cout << "min stack is: " << result << std::endl;
    s.pop();

    flag = s.min(result);
    if (flag) std::cout << "min stack is: " << result << std::endl;
    
    s.push(3);
    s.push(1);

    flag = s.min(result);
    if (flag) std::cout << "min stack is: " << result << std::endl;
}


/**
 * 132. 判断入栈，出栈顺序是否合法
*/
void test_is_correct_for_stack() {
    std::vector<int> instack = {1,2,3,4,5};
    std::vector<int> outstack = {4,3,5,1,2}; //{4,3,5,2,1}; //{4,3,5,1,2}; //{4,5,3,2,1};
    bool result = sword_finger_offer::is_correct_for_stack(instack, outstack);
    std::cout << "is correct for stack: "<< std::boolalpha << result << std::endl;
}

/**
 * 133. z字打印二叉树, 同66
 * 方法２使用两个栈实现,左右子树的入栈顺序和奇偶行有关
*/
void test_z_print() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(6);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(9);
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(4);
    // sword_finger_offer::print_binary_tree_with_z(root);
    sword_finger_offer::print_binary_tree_with_z_v2(root);
}

/**
 * 测试vector按照下标赋值，再使用begin, size等函数会有问题．插入数据应该用pushback
*/
void test_reversetest_reverse() {
    std::vector<int> tmp1;
    std::vector<int> tmp2;
    tmp1.reserve(2);
    // tmp1[0] = 1;
    // tmp1[1] = 2;
    tmp1.push_back(1);
    tmp1.push_back(2);

    std::cout << "tmp1 size: " << tmp1.size() << " cap: " << tmp1.capacity() << std::endl;
    for (int i=0; i<tmp1.size(); i++) std::cout << tmp1[i] << " ";
    std::cout << std::endl;
    std::cout << "tmp1 reverse\n";
    // std::reverse(tmp1.begin(), tmp1.end());
    // for (int i=0; i<2; i++) std::cout << tmp1[i] << " ";
    for (auto iter=tmp1.rbegin(); iter!=tmp1.rend(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

}

/**
 * 134. 判断序列是否为二叉平衡树的后续排列
*/
void test_check_bst_order() {
    std::vector<int> vec = {7,4,6,5}; //{5,7,6,9,11,10,8};
    bool result = sword_finger_offer::check_binary_search_tree_order(vec);
    std::cout << "check bst order: " << std::boolalpha << result << std::endl;
}

/**
 * 135. 打印二叉树中和为某值的路径
*/
void test_sum_path(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    // std::vector<std::vector<int>> result = sword_finger_offer::sum_path(root, 8);
    // for (int i=0; i<result.size(); i++) {
    //     for (int j=0; j<result[i].size(); j++) {
    //         std::cout << result[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    sword_finger_offer::sum_path_v2(root, 3);
}

/**
 * 136. 将二叉树转换成双向链表, 其思路是dfs, 输入为当前节点root,和root节点之前最后一个节点的指针地址，即遍历root->left, root->left=*last; *last->right=root, 遍历root->right.
 * 注意更新last node的内容时，　不能写成last=*root, 应该写成*last=root, 保证last地址不变．其last地址不能由函数返回，　因为函数中首先有使用last, 再更新last.
 * 
*/
void test_bst2list() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(8);
    TreeNode* last = nullptr;
    sword_finger_offer::bst2list(root, &last);
    TreeNode* head = sword_finger_offer::get_list_head(last);
    while (head != nullptr)
    {
        std::cout << head->val << " ";
        head = head->right;
    }
    std::cout << std::endl;
}

/**
 * 137. 序列化，反序列化二叉树, 注意反序列化的时候string的index要在最开始++
*/
void test_serialize_deserialize() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(9);
    std::string oss = sword_finger_offer::serialize(root);
    TreeNode* head = sword_finger_offer::deserialize(oss);

    std::cout << "serialized: " << oss << std::endl;

    sword_finger_offer::print_bst(head);

    char* fileName = "test.txt";
    ofstream fileOut;
    fileOut.open(fileName);
    sword_finger_offer::serialize_ss(root, fileOut);
    fileOut.close();

    head = nullptr;
    ifstream fileIn;
    fileIn.open(fileName);
    sword_finger_offer::deserialize_ss(&head, fileIn);
    fileIn.close();

    std::cout << "iostream serialize, deserialize:\n";
    sword_finger_offer::print_bst(head);
}


/**
 * 138. 生成排列,组合．其中组合是将当前idx的字符push 进comb, 并且将历史的comb ＋　str[idx]添加进comb
 * 
*/
void test_permutation() {
    std::string str = "abc";
    // std::vector<std::string> result = sword_finger_offer::permutation(str);
    std::vector<std::string> result = sword_finger_offer::combinations(str);
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << std::endl;
    }
}

/**
 * 139. ８皇后问题，　正方体８角和
*/
void test_queen_permute() {
    std::vector<std::vector<int>> result = sword_finger_offer::queen_permutation(8);
    std::cout << "eight queen size:" << result.size() << std::endl;
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * 140. 查找超过一半的数
*/
void test_morethanhalf() {
    std::vector<int> arr = {4,3,2,3};
    int result = sword_finger_offer::MoreThanHalf(arr);
    std::cout << "more than half result: " << result << std::endl;
}

/**
 * 141. 查找ｋ个最小数. 共四种方法：
 * 1. partition
 * 2. 手写最大堆，　注意初始化堆时，从length/2-1 --> 0,调整堆的顺序，后面依次从k->arr.length判断是否入堆
 * 3. 用make_heap, pop_heap, push_heap等
 * 4. 使用multiset<int, std::greater>, 直接维护最大堆
*/

void test_topKminus() {
    std::vector<int> arr = {3,4,2,5,1, 2};
    int k = 4;
    // std::vector<int> result = sword_finger_offer::TopKminus(arr, k);
    // std::vector<int> result = sword_finger_offer::TopKminus_with_heap(arr, k);
    // std::vector<int> result = sword_finger_offer::TopKminus_with_makeheap(arr, k);
    std::vector<int> result = sword_finger_offer::TopKminus_with_set(arr, k);
    std::cout << "top " << k << " minus: ";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 142. 流数据的中位数. 
 * １.使用partition方法，　分别找出median, median+1的数即可，但该方法要求读取数组所有数据．
 * ２．即时读取，维护最大最小堆．
 * ３．主要std::push_heap, std::multiset中设置最大堆，最小堆的方法．　multiset通过初始化设置，　默认最小堆，即std::less<T>，　最大堆std::greater<T>; 
 *        std::push_heap等，默认最大堆，　std::less<T>(). 
 * 即 std::push_heap默认最大堆，取反用std::greater<T>(), std::multiset默认最小堆，　取反用std::greater<T>
*/
void test_median_number() {
    std::vector<int> arr = {3,2,4,1,5,6};
    // int result = sword_finger_offer::median_number(arr);
    // int result = sword_finger_offer::median_number_with_set(arr);
    // float result = sword_finger_offer::median_number_V2(arr);
    float result = sword_finger_offer::median_number_V3(arr);

    std::cout << "result: " << result << std::endl;
}

void test_heap() {
    std::vector<int> arr;
    arr.push_back(1);
    std::push_heap(arr.begin(), arr.end());
    arr.push_back(2);
    std::push_heap(arr.begin(), arr.end(), std::greater<int>());



    std::multiset<int, std::greater<int>> set;
    set.insert(1);
    set.insert(2);
}

/**
 * 143. 连续子串最大和
*/
void test_continuoussum() {
    std::vector<int> arr = {-4,-3,-2,-6,-5};
    int result = sword_finger_offer::continuoussum(arr);
    std::cout << "result: " << result << std::endl;
}

/**
 * 144. 序列中１出现的次数. 递归思想．　如21345，　可拆成０->1345, 1346->21345两部分，　0->1345可递归求解．
 * 1346->21345中包含的１个数可分为：最高位的１出现的次数part1和其他位出现的次数part2．如果最高位是１，　则part1=int(str.substr(idx+1)) +1, 否则part1=10**(str.length-idx-1);
 * 其他位出现的次数part2=最高位的值＊len(str.length-idx-1)*10**(str.length-idx-2). 如21345的part2=2*4*1000.　
 * 2表示两万个数，后面４位，每一位都包含０－９的遍历．相当于0000->9999重复２遍，　当其中一位为１时，其他三位随意共有1000种可能．即part2 = 2 * 4 * 1000
*/
void test_one_counts() {
    int result = sword_finger_offer::one_counts(1345); // 5, 12, 10,  55, 99, 10000, 21345
    std::cout << "result: " << result << std::endl;
}


/**
 * 145. 编辑距离．　共有３种操作．　插入，删除，替换．
 * dp求解．　求word1的０－＞ｉ，与word2的０－＞j的编辑距离．　共有三种方式到达a[i][j]：
 * 1. a[i-1][j-1]表示替换，　即word1的第ｉ个字符替换成word2的第ｊ个字符． 如horse, ros, a[5,3]--> a[4,2] hors->ro, 将e替换成s即可
 * 2. a[i-1][j]表示删除， 因为word1的前ｉ－１个字符已经与word2的ｊ个字符匹配，故删除第i个字符，如hors->ros, 删除e
 * 3. a[i][j-1]表示插入，因为word1的ｉ个字符已经和word2的j-1个字符匹配，故只能额外插入字符达到a[i][j], 如horse->ro, 插入ｓ
 * 再刷感想：1. 注意word1[i]==word2[j]时，dp[i][j]直接等于dp[i-1][j-1]
*/
void test_mindistance() {
    std::string word1 = "intention"; // "horse";
    std::string word2 = "execution"; // "ros";
    // int result = dp::minDistance(word1, word2);
    // int result = dp::minDistance_v2(word1, word2);
    int result = dp::minDistance_v3(word1, word2);
    std::cout << "result: " << result << std::endl;
}

/**
 * 146. 简化ｕnix路径，　使用栈, １．注意substr的用法，　第二个参数是个数，而不是末尾下标; 2.注意连续//会产生空字符串．
*/
void test_simplepath() {
    std::string path = "/a//b////c/d//././/.."; //"/a/../../b/../c//.//"; // "/a/./b/../../c/"; // "/home//foo/"; // "/../"; // "/home/";
    std::string result = stack_algs::simplepath(path);
    std::cout << "simple path result: " << result << std::endl;
}

/**
 * 147. 序列中第index的数字. z主要分为3部分：
 * １. 求得对应位数数字一共的位数，如个位数，总共９位，　二位数：2*90, 3位数：3*900. 
 * 2. 得到开始的位数的起始点，如1，　１０，　１００
 * 3. 求得具体数字，第ｉ位的值
 * 注意：1中求对应位的数字个数要乘上n
 * 
*/
void test_number_of_digit() {
    int result = sword_finger_offer::numberofindex(190); // 10, 11, 13, 1000, 190
    std::cout << "number of digit: " << result << std::endl;
}

/**
 * 147. 生成最小数, 通过将arr中所有数字转换成string,避免大数问题，　同时转换成对string数组的排序问题，比较string a,b可定义成a+b , b+a的大小比较．升序排序即为最小组合数．
*/
void test_mincombination() {
    std::vector<int> arr = {3, 321, 32};
    std::string result = sword_finger_offer::mincombination(arr);
    std::cout << "mincombination result: " << result << std::endl;
}

/**
 * 148. 数字转字符的排列组合数. 简单dp问题, 如果str[i-1:i] <=25, 则dp[i]=dp[i-1]+dp[i-2],
 * 否则　dp[i]=dp[i-1]
 * 注意dp[0]应该初始化为１，而不是０，如12, dp[2]=dp[1]+dp[0], 如果dp[0]=0, 结果不对
*/
void test_number2ascii() {
    int number = 11258;
    int result = sword_finger_offer::number2ascii(number);
    std::cout << "number2ascii result: "<< result << std::endl;
}

/**
 * 149. 礼物最大价值, 简单dp[i,j]=max(dp[i-1, j], dp[i, j-1]) + val[i,j]. 其中dp数组可以只使用一行，重复利用
*/
void test_giftmaxval() {
    std::vector<std::vector<int>> arr = {{1, 10, 3, 8}, {12, 2, 9, 6}, {5, 7, 4, 11}, {3, 7, 16, 5}};
    int result = sword_finger_offer::giftmaxval(arr);
    std::cout << "git max val result: " << result << std::endl;
}

/**
 * 150 最长不重复子串长度. 两种方法：1. 滑窗
 * ２. dp方法，　使用position[26]记录历史字符最近出现的下标．　
 * 如果ｉ - position[str[i]-'a'] <= dp[i-1], dp[i]=i - position[str[i]-'a'], 
 * 否则 dp[i]=dp[i-1] + 1;
 * 因为只涉及到dp[i],dp[i-1], 可直接使用单个变量计算
 * 
*/
void test_longest_substr() {
    std::string str = "arabcacfr";
    // int result = sword_finger_offer::longest_substr(str);
    int result = sword_finger_offer::longest_substr_v2(str);
    std::cout << "longest substr result: " << result << std::endl;
}

/**
 * 151. 丑数
 * 记录x2, x3, x5的最小丑数，下一个丑数＝min(mult2*2, mult3*3, mult5*5)
 * 记录当前最小的丑数要注意是<=, 而不是<, 如while((*mult2)*2<=curr_num) mult2++;
*/
void test_ugly_number() {
    int result = sword_finger_offer::ugly_number(5); // 1,2,3,4,5
    std::cout << "ugly number result: "<< result << std::endl;
}

/**
 * 153. 第一次只出现一次的数.遍历一遍先求得各个字符出现的次数，然后再遍历原始数组，看map中map[ch]是否存在＝＝1. 
 * 注意第二次确定是否存在１的数，必须遍历原始数组，而不能依次遍历map, 因为map的顺序并不是按照原始数组的先后顺序排列．
 * 另一种方法是滑窗．当map[begin]>=2时　begin++, 一直map[ｉ]++, 则最后map[begin]的字符即为第一个字符．　注意当map[begin]>=2时，不能删除该元素，若删除，　当其出现次数＞２时，这会有问题．
 *
*/
void test_first_one_char() {
    std::string str = "dcbcdbc";
    // char ch = sword_finger_offer::first_one_char(str);
    // char ch = sword_finger_offer::first_one_char_v2(str);
    char ch = sword_finger_offer::first_one_char_v3(str);
    std::cout << "first one char result: " << ch << std::endl;
}

/**
 * 154.　逆序对
*/
void test_count_reverse_pair() {
    std::vector<int> arr = {4, 5, 6, 7};
    int result = sword_finger_offer::count_reverse_pair(arr);
    std::cout << "count reverse pair result: " << result << std::endl;
}

/**
 * 155. 求得两个链表的第一个公共节点
*/
void test_common_node() {
    ListNode* root = new ListNode(1);
    root->next = new ListNode(2);
    root->next->next = new ListNode(3);
    root->next->next->next = new ListNode(4);
    ListNode* root2 = new ListNode(5);
    root2->next = new ListNode(6);
    // root2->next->next = root;
    ListNode* common_node = sword_finger_offer::first_common_node(root, root2);
    if (common_node != nullptr) {
        std::cout << "test common node result: " << common_node->val << std::endl;
    }
    else {
        std::cout << "test common node result: has no common node\n";
    }
}

/**
 * 156 求二叉树中任意两节点的最小公共父节点. dfs求解．　定义 dfs(root, node1, node2), 如果root等于node1或node2,　则返回root, 
 * 依次查找dfs(root->left, node1, node2), dfs(root->right, node1, node2)
 * 如果left存在node1或node2, 且right存在node1或node2,则当前root为parent node, 否则返回left或right
*/
void test_treenode_common_parent() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    TreeNode* parent = sword_finger_offer::lastest_common_parent(root, root->left, root->left->right);
    if (parent != nullptr) {
        std::cout << "test treenode common parent result: " << parent->val << std::endl;
    }
    else {
        std::cout << "test treenode common parent result: has no common node\n";
    }
}

/**
 * 157 排序数组中某个数字的个数. 使用partition方法先找出num数字在数组中第一个，最后一个数字的下标．
 * 注意要考虑num不在数组中的情况，不能直接left==right就返回left, 返回值应该在arr[mid]==num时，才返回．
*/
void test_sorted_arr_count() {
    std::vector<int> arr = {1,1,2,2,2,3,3,5};
    // int result = sword_finger_offer::sorted_arr_count(arr, 5);
    int result = sword_finger_offer::sorted_arr_count_v2(arr, 4);
    std::cout << "test sorted arr count result: " <<  result << std::endl;
}

/**
 * 158 从二叉树中找出第k大的节点. 先序遍历即可．同时记录k.要对k加引用，保证dfs深层修改的k值能被反映到上层中．
 * 因为dfs是自顶向下的，而遍历节点是自底向上的，故底层要反馈信息给上层，需要对k加引用．
*/
void test_kthnode() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(8);
    TreeNode* node = sword_finger_offer::kthNode(root, 8);
    if (node != nullptr) {
        std::cout << "test kthnode: " << node->val << std::endl;
    }
    else {
        std::cout << "test kthnode is nullptr\n";
    }
}

/**
 * 159 二叉树的深度
*/
void test_depthofBST() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    // root->left->left = new TreeNode(1);
    // root->left->right = new TreeNode(3);
    // int depth = sword_finger_offer::depthOfTreeNode(root);
    int depth = sword_finger_offer::depthOfTreeNode_v2(root);
    std::cout << "depth of bst: " << depth << std::endl;
}

/**
 * 160 判断是否为平衡二叉树. 递归判断．递归需要返回两个信息: 1.子数是否为平衡树，2.子树的depth．
 * 可以定义　bool dfs(treenode* root, int& depth); 
 * 也可定义　std::pair<bool, int> dfs(treenode* root);
 * 分别来返回这两个值
*/
void test_balance_tree() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    // root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    // root->left->right = new TreeNode(3);
    // root->right->left = new TreeNode(6);
    // root->right->right = new TreeNode(8);

    bool result = sword_finger_offer::check_balance_tree(root);
    std::cout << "balance tree result: " << std::boolalpha << result << std::endl;
}

/**
 * 161 找出数组中唯一出现一次的两个数字. 因为数组中有两个不同的数，故先找出两个不同数最低比特位不同的位置．
 * 根据该位置的０，１数值将数组划分为两类．然后对两类数字分别找出唯一出现一次的数．
 * 注意：符合优先级，＆的优先级低于＝＝，　故划分数组时判断条件为((flag&num)==0), 不可写成(flag&num==0)
*/
void test_appearOnce() {
    std::vector<int> arr = {2,4,3,6,3,2,5,5};
    std::pair<int, int> result = sword_finger_offer::appearOnce(arr);
    std::cout << "appear onece result: " << result.first << ", " << result.second << std::endl;
}

/**
 * 162. 找出数组中唯一出现一次的数字，其他数字出现三次．
 * 思路：记录每个比特位中１出现的次数,最后按位％３,得到出现一次的数字．注意:(int&int)得到的结果还是ｉnt,
 * 判断num&bitmask对应位是否为１的方法不是（num&bitmask）== 1, 其值应该是　(num&bitmask) == bitmask,或写成　(num & bitmask) != 0
 * 2. 基于上一思路，可以直接使用int one, two, three, 分别记录出现１，２，３次的比特．见题９.
 * 注意two的更新要考虑历史two的信息，而three则不能考虑历史信息，如当one=0, two=3, three=2, num=1
 * num=1时，two应该等于two=two|(one&num)=3, 而不是one&num=0, one=one^num=1, three=two&one=1, 而不是three=three|(two&one)=3,
 * three等于３的话会导致更新two, one出错
*/
void test_appearOnce_of_three() {
    std::vector<int> arr = {1,-5,3,1,3,1,3}; //{1,-5,1,1}; //{1,-5,3,1,3,1,3};
    // int result = sword_finger_offer::appearOnce_of_three(arr);
    int result = sword_finger_offer::appearOnce_of_three_v2(arr);
    std::cout << "appear once of three result: " << result << std::endl;
}

/**
 * 163. 找出排序数值中和为s的两个数
*/
void test_sum_of_s() {
    std::vector<int> arr = {1,1,2,4,5,7,7,9};
    int s = 1;
    std::pair<int, int> p = sword_finger_offer::sum_of_s(arr, s);
    std::cout << s << " = " << p.first << " + " << p.second << std::endl;
}

/**
 * 164 找出和为s的所有连续数字序列
*/
void test_sum_of_s_v2() {
    int s = 4;
    std::vector<std::vector<int>> result = sword_finger_offer::sum_of_s_v2(s);
    std::cout << "sum of " << s << std::endl;
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * 165 翻转字符串
*/
void test_reverse_str() {
    std::string str = "I"; //"I am a student.";
    std::string result = sword_finger_offer::reverse_str(str);
    std::cout << "reverse str result: " << result << std::endl;
}

/**
 * 166 得到数组中窗口为k的所有最大值. 两种方法：1.使用multipset维护一个最大堆，同时删除前idx-2的数，若使用vector+make_heap或自己实现的heap, 删除操作不太好处理;
 * 2.使用deque，双向队列中只保留windows内最大值的降序排序, 如果当前idx,arr[idx]> dequeue[arr[deque.back()]] deque.pop();
 * 如果deque.front()的下标超出了当前windows范围，则pop front(), 再push_back当前idx, 当前窗口的最大值即为，　deque.front()
 * 
 * 再刷感想：
 * 在当前idx下比较arr[list.back()] <= arr[idx]，　而不是 list.front(), 且使用while而不是if
*/
void test_max_sequence() {
    std::vector<int> arr = {2,3,4,6,2,5,1};
    int windows = 3;
    // std::vector<int> result = sword_finger_offer::max_sequence(arr, windows);
    // std::vector<int> result = sword_finger_offer::max_sequence_v2(arr, windows);
    // std::vector<int> result = sword_finger_offer::max_sequence_v3(arr, windows);
    std::vector<int> result = sword_finger_offer::max_sequence_v4(arr, windows);
    std::cout << "max sequence result:\n";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 167 n个骰子出现的数字之和的所有概率. dfs生成所有可能的组合．注意使用vector.reverse后，　然后直接使用[i]下标设值，　begin(), end()会有问题．
*/
void test_probability_n() {
    int n = 1;
    std::unordered_map<int, float> result = sword_finger_offer::probability_n(n);
    std::cout << "probability " << n << std::endl;
    for (auto& p : result) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
}

/**
 * 168 扑克牌中的顺子. 先对数字进行升序排序．１．找出０的个数; 2. 对非０个数依次求其间隔．　如果间隔总数小于等于０的个数，则可以是顺子；
 * 注意：1. 求非零数字间隔时要去除第一个非零数字与０的间隔．２．要考虑出现相同数字的情况，即对子
*/
void test_is_continuous() {
    std::vector<int> arr = {2, 4, 7, 0, 0};
    bool result = sword_finger_offer::isContinuous(arr);
    std::cout << "test is continuous result: " << std::boolalpha << result << std::endl;
}

/**
 * 169 圆圈中最后剩下的数字. 两种方法：1. 模拟法，　模拟该过程，　注意最后一个数并不是删除n-1个数的下标+1, 而应该遍历数组，直到找到该数．
 * ２. 数学推到公式：　f(n,m) = (f(n-1, m)+m)%n;
*/
void test_final_number() {
    int n=5;
    int m=3;
    for (n=1; n<=5; n++) {
        // int result = sword_finger_offer::finalNumber(n,m);
        int result = sword_finger_offer::finalNumber_v2(n,m);
        std::cout << "test final number (" << n << ", " << m <<")" << ": " << result << std::endl;
    }   
}

/**
 * 170 最大股票利润
*/
void test_maxprofit() {
    std::vector<int> arr = {9, 8, 5}; //{9, 11, 8, 5, 7, 12, 16, 4};
    int result = sword_finger_offer::maxprofit(arr);
    std::cout << "test max profit: " << result << std::endl;
}

/**
 * 171 求１＋２＋....+n　的方法
*/
void test_nsum() {
    int n = 1;
    int result = sword_finger_offer::nsum(n);
    std::cout << "test sum of n: " << result << std::endl;
}

/**
 * 173 位运算求两数之和. 模拟求和过程．负数也同样适用于
*/
void test_sum_of_bits() {
    int num1 = 5;
    int num2 = -6;
    int result = sword_finger_offer::sum_in_bits(num1, num2);
    std::cout << "test sum of bits: " << result << std::endl;
}

/**
 * 174 不用除法做连乘. 计算A[0...n-1]/A[i]=A[0....i-1] * A[i+1...n-1]
 * 分别求出heads[i]，表示A[0]到A[i]连乘的结果;
 * tails[i]表示A[n-1]到A[i]连乘的结果;
 * 注意: heads[0]应该等于A[0],而不是１，tails[n-1]应该等于A[n-1],而不是１
*/
void test_multipy() {
    std::vector<int> arr = {2,-1,0,-4,3};
    std::vector<int> result = sword_finger_offer::multipy(arr);
    std::cout << "test multipy result: ";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * 175 频率最高的前ｋ个数. 这种top k的题目，应该想到用最大最小堆．
 * 先求得各个元素的出现次数，key->val．然后用最小堆存储ｖal->key的multipset存pair(val,key), 并按照val降序排列．
*/
void test_topkFrequent() {
    std::vector<int> arr = {1,1,1,2,2,3};
    int k=2;
    // std::vector<int> result = sort::topKFrequent(arr, k);
    std::vector<int> result = sort::topKFrequent_v2(arr, k);
    std::cout << "test topk frequent:";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * 176 求h_index. 两种方法：１. 对indexs进行升序排序．从数组末尾往前遍历，判断arr_size - idx < arr[idx], 直到arr_size - idx >= arr[idx], 结果为arr_size - idx;
 * 2. 根据数组生成优先级队列．其复杂度略低于排序，得到最大堆，依次pop(), 并ans+1, 知道top()>=ans为止．
*/
void test_h_index() {
    std::vector<int> citations = {3,0,6,1,5};
    int result = sort::h_index(citations);
    // int result = sort::h_index_v2(citations);
    std::cout << "test h index:" << result << std::endl;
}

/**
 * 177 判断有效括号. 注意比较st.top()和当前s[i]字符结果时，要先判断 st.empty()
*/
void test_valid_parentness() {
    std::string s = "{[]}";
    bool result = stack_algs::isValid_parentness(s);
    std::cout << "test valid parentness: " << s << " result:" << std::boolalpha << result << std::endl;
}

/**
 * 178. 查询/插入　数字到数组中．二分查找，可以使用dfs, 也可直接while
 * 因为数组中可能没有target．二分查找不能将区间分为[left, mid-1], [mid+1, right] 应该将其划分为[left, mid], [mid+1, right]
 * 如[1,3,5,6], target=2, 假设查询区间的右边界一定大于或等于target, 则在mid=(0+3)/2=1时，　(nums[1] < target==false)--> 应该遍历[left, mid]=[0, 1]区间，而不是[left, mid-1]=[0,0]
 * [left, mid-1]使得区间并不满足右边界一定大于或等于target．
*/
void test_searchinsert() {
    std::vector<int> arr = {1,3,5,6};
    // int result = binary_search::searchInsert(arr, 0);
    int result = binary_search::searchInsert_v2(arr, 0);
    std::cout << "test search insert result: " << result << std::endl;
}

/**
 * 179. 合并中间区间
*/
void test_merge_intervals() {
    std::vector<std::vector<int>> intervals = {{1,3},{15, 18},{8, 10}, {2, 6}};
    std::vector<std::vector<int>> result = binary_pointer::merge_intervals(intervals);
    std::cout << "test merge intervals:\n";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i][0] << ", " << result[i][1] << " ";
    }
    std::cout << std::endl;
}

/**
 * 180. 最小路径和, dp求解　dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
 * 注意初始化第一行，第一列时，dp[i][0] = dp[i-1][0] + grid[i][0], 而不是直接等于grid[i][0];
 * 
*/
void test_minpathsum() {
    std::vector<std::vector<int>> grids = {{1,3,1},{1,5,1},{4,2,1}};
    int result = dp::minPathSum(grids);
    std::cout << "min path sum result: " << result << std::endl;
}

/**
 * 181. 排序三色旗. 1. 普适性的方法直接使用快排，　分块排序时，要判断low/high与index的大小，　只有low <index，　或high>index才qsort
 * 2. 因为只有３中种数字．　分别记录０,2数字的最右，最左下标p0, p2; 然后遍历p0+1 ->p2-1; 
 * 如果vec[curr]==1 curr+1继续遍历;
 * 如果vec[curr]==0, 则交换vec[curr], vec[p0+1]的值，　然后curr, p0加一, 该两者交换，p0+1的值肯定为１
 * 如果vec[curr]==2, 则交换vec[curr], vec[p2-1]的值，　然后p2-1, 但curr不能加一．因为p2交换到curr的数字可能为０
*/
void test_sort_color() {
    std::vector<int> arr = {2,0,2,1,1,0};
    sort::sortColors(arr);
    std::cout << "sort color result:\n";
    for (int i=0; i<arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 182. 遍历查找数组是否存在board中. dfs 遍历．
 * 从所有节点为起点．进行dfs, 注意起始点特殊处理visited, 并且dfs的起始点从第二个点开始．
*/
void test_exist_board() {
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'}, 
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};
    std::string word = "ABCB"; //"SEE"; //"ABCB";
    bool result = dfs::exist(board, word);
    std::cout << "test exist board result: " << std::boolalpha << result << std::endl;
}

/**
 * 183. 迭代对二叉树进行中序遍历. 使用栈模拟递归．即按照递归的顺序将节点push到stack中．一般为两重循环．
 * while(!st.empty() || ptr) { // 避免st空或右子树为空的情况
 *  while (ptr) {st.push(ptr), ptr=ptr->left}; top=st.top(); st.pop(); ptr=top->right;
 * }
*/
void test_inorder_travel() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    std::vector<int> result = stack_algs::inorderTraversal(root);
    std::cout << "test inorder travel:";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * 184. 求二叉搜索树的组合数, dfs或dp求解．　dp[i,j] = sum (dp[i,k-1] * dp[k+1][j];) k=i-->j
*/
void test_num_tree() {
    int n = 3;
    // int result = dfs::numTrees(n);
    int result = dp::numTrees(n);
    std::cout << "test num tree result: " << result << std::endl;
}

/**
 * 185. 将二叉树按层输出
*/
void test_levelorder() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    std::vector<std::vector<int>> result = queue_alg::levelOrder(root);

    std::cout << "test level order result:\n";
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j < result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}

/**
 * 186. 将二叉树转换成链表. 三种思路
 * １．TreeNode* flatten_dfs(TreeNode*, TreeNode*&), 依次flatten左子树，右子树，并返回当前树的头，尾，则root->right=dfs(root->left, pre), pre->right = dfs(root->right, pre), 此时要注意左子树为空的情况，pre=root.
 * 2. 同样dfs,分别先flatten　左右子树．　但不记录last node，在root->left不为空的情况下，while循环遍历找出左子树的最右节点last．则last->right = root->right; root->right=  root->left; root->left=nullptr;
 * 3. 迭代计算．转换成链表，其实就是当左子树不为空时，将左子树放到右子树，　然后原来的右子树放到左子树的最右节点．然后root=root->right遍历，直到root为空
*/
void test_flatten() {
    TreeNode* root = new TreeNode(3);
    // root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    // root->right->right = new TreeNode(7);
    // dfs::flatten(root);
    // dfs::flatten_V2(root);
    dfs::flatten_V3(root);

    std::cout << "test flatten result:\n";
    while(root!=nullptr) {
        std::cout << root->val << " ";
        root = root->right;
    }
    std::cout << std::endl;
}

/**
 * 187. 求最大股票收益. 记录历史收益pre, 如果pre>=0, 则累加prices[i]-prices[i-1]
 * 否则，　pre=prices[i]-prices[i-1]
*/
void test_max_profit() {
    std::vector<int> arr = {7,1,5,3,6,4};
    int result = search::maxProfit_v4(arr);
    std::cout << "test max profit result:" << result << std::endl;
}

void test_tmp() {
    int a = INT32_MIN;
    int mina = - INT32_MIN;
    int maxa = INT32_MAX;
    int minmaxa = - INT32_MAX;
    std::cout << "a :" << hex << a << ", mina: " << hex << mina 
              <<", maxa: " << hex << maxa << ", minmaxa: " << hex << minmaxa << std::endl;
}

/**
 * 188. 找出数组中单个数字
*/
void test_single_number() {
    std::vector<int> arr = {1,2,2};
    int result = bits_alg::singleNumber(arr);
    std::cout << "single number is: " << result << std::endl;
}

/**
 * 189. 判断单词划分，　同７
*/
void test_wordBreak_simple(){
    string s = "catsanddog";
    std::vector<std::string> dicts = {"cat", "cats", "and", "sand", "dog"};
    bool result = dp::wordBreak_single(s, dicts);
    std::cout << "simple wordbreak: "  << result << std::endl;
}

/**
 * 190. 找出循环链表中的开始节点
 * 思路：用步数为１，２分别找出相同点，然后以ｓｔｅｐ１走到第一个公共节点．
 * 注意：链表只有一个单独节点的情况．要额外判断．
*/
void test_detectcycle() {
    ListNode* head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);
    head->next->next->next->next = head->next;
    ListNode* result = listnode_alg::detectCycle(head);
    if (result!=nullptr) {
        std::cout << "test detect cycle result: " << result->val << std::endl;
    }
    else {
        std::cout << "test detect cycle result is nullptr\n";
    }
}

/*********************************************************************************/
/********************************** hot 100 **************************************/
/*********************************************************************************/
/**
 * 1. 第ｋ个最大值
*/
void test_findkthlargest_hot_100() {
    std::vector<int> arr = {3,2,1,5,6,4};
    int k=2;
    // int result = hot_100::findKthLargest(arr, k);
    int result = hot_100::findKthLargest_min_heap(arr, k);
    std::cout << "test findkthlargest result: " << result << std::endl;
}

/**
 * 2. 滑动窗口最大值
 * 注意使用双向队列．　存放ｋ窗口中降序下标．
 * １．当当前节点值大于dequeue.back时，pop_back,而不是判断当前节点值大于dequeue.front()
 * ２．判断当前front最大值是否超过了k时，也要判断dequeue是否为空，因为k=1时，初始化queue时是空的
*/
void test_max_sliding_window_hot_100() {
    std::vector<int>  nums = {1,3,1,2,0,5}; //{1,3,-1,-3,5,3,6,7};
    int k = 3;
    // std::vector<int> result = hot_100::maxSlidingWindow(nums, k);
    std::vector<int> result = hot_100::maxSlidingWindow_v2(nums, k);
    std::cout << "test max sliding windos:" ;
    for (int i=0; i<result.size(); i++) std::cout << result[i] << " ";
    std::cout << std::endl;
}

/**
 * 3. 搜索二维矩阵
 * 从左下角开始搜，如果［row_idx, col_idx］ > target, 往上走row_idx--; 否则col_idx++;
 * 注意row_idx可能出现小于０的情况，而不会出现＞row的情况
*/
void test_searchMatrix_hot_100() {
    std::vector<std::vector<int>> matrix = {{-1, 3}}; // {{1,4,7}, {2,5,8},{3,6,9}};
    int target = 1; //5;
    bool result = hot_100::searchMatrix(matrix, target);
    std::cout << "test search matrix result: " << std::boolalpha << result << std::endl;
}

/**
 * 4. 完全平方数.　完全0/1背包问题
 * 注意初始化的时候dp[0]=0, 其他为INT_MAX, 然后遍历寻找最小值
*/
void test_numsquare_hot_100() {
    int n =13;
    int result = hot_100::numSquares(n);
    std::cout << "test numsquare result: " << result << std::endl;
}

/**
 * 5. 最长上升子序列
 * 1. 刚开始以为是用栈，求得包含当前值的升序序列，但该种方法忽略了历史最有子序列．
 * 如{1,3,6,7,9,4,10}, 栈方法是会得到{1,3,4,10},而最长的升序应该是{1,3,6,7,9,10}
 * ２．使用ｄｐ方法，如果nums[i]大于nums[j]则dp[i]可以由dp[j]+1得到，
 * 然后从０到ｉ－１遍历j得到０－＞ｉ的最长升序子序列
 * ３．　结果并不是返回dp[n-1],而应该记录整个过程的最大值．
*/
void test_lengthofLIS_hot_100() {
    std::vector<int> arr = {1,3,6,7,9,4,10,5,6}; //{10,9,2,5,3,7,101,18};
    // int result = hot_100::lengthOfLIS(arr);
    int result = hot_100::lengthOfLIS_V2(arr);
    std::cout << "test length of LIS result: " << result << std::endl;

}

/**
 * 6. 根据身高重建队列
*/
void test_reconstruct_queue_hot_100() {
    std::vector<std::vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    std::vector<std::vector<int>> result = hot_100::reconstructQueue(people);
    std::cout << "test reconstruct queue:\n";
    for (int i=0; i<result.size(); i++) {
        std::cout << result[i][0] << ", " << result[i][1] << std::endl;
    }
}

/**
 * 7. 路径总和
 * 思路：　dfs求解．刚开始只考虑到一层ｄｆｓ，导致逻辑有点错误．
 * １．　dfs(root->left, target, cnt), dfs(root->right, target , cnt)
 * 然后　dfs(root->left, target - root->val, cnt), 
 *      dfs(root->right, target-root->val, cnt)
 * 该重dfs其实是结果等于target或target-root->val的结果．而不是结果为target的结果．
 * 应该两层dfs. 第一层　
 * dfs(root, sum, cnt), 
 * dfs(root->left, sum, cnt), 
 * dfs(root->right, sum, cnt)
 * 第二层dfs:
 * dfs_two(root->left, sum-root->val, cnt)
 * dfs_two(root->right, sum-root->val, cnt)
 * 
*/
void test_pathsum_hot_100() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);
    int target = 8;
    int result = hot_100::pathSum(root, target);
    std::cout << "test pathsum result: " << result << std::endl;
}

/**
 * 8. 找到消失的数字. 通过将nums中的数字映射成下标idx=(nums[i]-1)%n, 然后将nums[idx]+=n, 
 * 最后遍历nums, 若nums[i]　<=n, 则ｉ＋１没出现在原始数组中
 * 
 * */
void test_find_disappearedNumbers_hot_100() {
    std::vector<int> nums = {4,3,2,7,8,2,3,1};
    std::vector<int> result = hot_100::findDisappearedNumbers(nums);
    std::cout << "test find disappeared numbers: ";
    for (int i=0; i<result.size(); i++) std::cout << result[i] << " ";
    std::cout << std::endl;
}

/**
 * 9. 观测每日温度
*/
void test_daily_temperatures_hot_100() {
    std::vector<int> T = {73,74,75,71,69,72,76,73};
    std::vector<int> result = hot_100::dailyTemperatures(T);
    std::cout << "test daily temperatures:";
    for (int i=0; i<result.size(); i++) std::cout << result[i] << " ";
    std::cout << std::endl;
}

/**
 * 10. 股票最大收益. dp＋状态转换
 * dp[i][0] 表示第i天结束，处于可以买入的状态的收益的最大值
 * dp[i][1] 表示第i天结束，手中有股票的状态的收益的最大值
 * dp[i][2] 表示第i天结束，处于冷冻期的收益的最大值
 * 注意初始化不应该全为０，　应该为INT_MIN, dp[0][0]=0
*/
void test_max_profit_hot_100() {
    std::vector<int> prices = {1,2,3,0,2};
    int result = hot_100::maxProfit(prices);
    std::cout << "test max profit: " << result << std::endl;
}

/**
 * 11. 戳气球dp求解，　状态转移方程　dp[i][j] = max(dp[i][j], dp[i][k]+dp[k][j]+points[i]*points[k]*points[j])
 * 注意是求points的ｉ,j,k数字乘积，而不是k,k-1,k+1
*/
void test_max_coins_hot_100() {
    std::vector<int> nums = {3,1,5,8};
    int result = hot_100::maxCoins(nums);
    std::cout << "test max coins: "<< result << std::endl;
}

/**
 * 12. 最短无序连续子数组. 使用单调栈，分别找出前后从未出过栈的下标．即求得出栈的下标中，最小，最大下标．
 * 则len = r - l +1
*/
void test_find_unsorted_sub_array_hot_100() {
    std::vector<int> nums = {2,6,4,8,10,9,15};
    int  result = hot_100::findUnsortedSubarray(nums);
    std::cout <<  "test find unsorted subarray result: " << result << std::endl;
}

/**
 * 13. 二叉树＋dp求解大家劫舍
*/
void test_rob() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);
    int result = hot_100::rob(root);
    std::cout << "test rob result: " << result << std::endl;
}

/**
 * 14. 比特位计数，dp求解，奇数比特位数等于dp[i-1]+1, 偶数=dp[i>>1]
*/
void test_count_bits() {
    int num = 5;
    std::vector<int> result = hot_100::countBits(num);
    std::cout << "test count bits result: ";
    for (int i=0; i<result.size(); i++) std::cout << result[i] << " ";
    std::cout << std::endl;
}

/**
 * 15. 字符串解码. 两种方法：栈方法或dfs
 * １．栈方法需要分别记录重复次数，和字符子串．注意记录的重复子串为上一层的结果，而不是当前重复子串的内容．注意num可能大于10
 * 2. dfs(s, index), 如果遇到s[ｉndex]=='['，则dfs(s, ++index). 并且res+= tmp_dfs_result * num. 注意num要重置０
*/
void test_decode_string() {
    std::string s = "3[a]2[bc]";; //"100[leetcode]"; //"3[a]2[bc]";
    // std::string result = hot_100::decodeString(s);
    std::string result = hot_100::decodeString_V2(s);
    std::cout << "test decode string result: " << result << std::endl;
}

/**
 * 16. 分割等和子集．　dfs．或０，１背包问题.
 * 1. dfs定义如下bool dfs(nums, index, target); 如果nums[idx]==target, return ture
 * 如果nums[idx] <target, return dfs(nums, index+1,target-nums[idx]) || dfs(nums, index+1, target)
 * 表示第ｉndex下标的数字取或不取．
 * ２．dp求解．dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i]]　表示第ｉ个数取或不取．
 * 注意是dp[i-1][j-nums[i]] 而不是　dp[i][j-nums[i]]，　dp[i][0]=true,表示前ｉ个数，达到０是否可行．
 * 3.由于dp[i][j]只与前一行dp[i-1]结果有关，可以直接定义dp[j]交替使用．此时遍历应该从j=target->0,
 * 这样可避免dp[j]=dp[j]||dp[j-nums[idx]]时，dp[j-nums[idx]]始终表示上一层的结果而不是统一层的结果．
*/
void test_can_partition() {
    std::vector<int> nums = {1,2,5}; //{1,5,11,5};
    // bool result = hot_100::canPartition(nums);
    // bool result = hot_100::canPartition_V2(nums);
    bool result = hot_100::canPartition_V3(nums);
    std::cout << "test can partition result: " << std::boolalpha << result << std::endl;
}

/**
 * 17 任务调度器
*/
void test_leastInterval() {
    std::vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n =2;
    int result = hot_100::leastInterval(tasks, n);
    std::cout << "test least interval result: " << result << std::endl;
}

/**
 * 18. 得到回文子串
*/
void test_count_substring () {
    std::string s = "aaa";
    int result = hot_100::countSubstrings(s);
    std::cout << "test count substring result: " << result << std::endl;
}

/**
 * 19. 最长递增序列
*/
void test_longest_increasing_path() {
    std::vector<std::vector<int>> matrix = {{9,9,4}, {6,6,8}, {2,1,1}};
    int result = thot_50::longestIncreasingPath(matrix);
    std::cout << "test longest increasing path result: " << result << std::endl;
}

/**
 * 20. 整数反转
*/
void test_reverse_thot50() {
    int n = 123;
    int result = thot_50::reverse(n);
    std::cout << "test reverse result: " << result << std::endl;
}

/**
 * 21. 全排列
*/
void test_permute_thot50() {
    std::vector<int> nums = {1,2,3};
    // std::vector<std::vector<int>> result = thot_50::permute(nums);
    std::vector<std::vector<int>> result = thot_50::permute_v2(nums);
    std::cout << "test permute thot50 result:\n";
    for (int i=0; i<result.size(); i++) {
        for (int j=0;j<result[i].size(); j++) std::cout << result[i][j] << " ";
        std::cout << std::endl;
    }
}

/**
 * 22. 求子集. dfs求解．一定要主要递归的下标为i+1, 而不是index+1, 然后push back的数组也不是nums[index],
 * 而是nums[i]
*/
void test_subset_thot50() {
    std::vector<int> nums = {1,2,3};
    // std::vector<std::vector<int>> result = thot_50::subsets(nums);
    std::vector<std::vector<int>> result = thot_50::subsets_v2(nums);
    std::cout << "test subsets result:\n";
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) std::cout << result[i][j] << " ";
        std::cout << std::endl;
    }
}

void test_generate_parenthesis_thot50() {
    int n = 3;
    std::vector<std::string> result = thot_50::legal_partness(n);
    std::cout << "test generate parenthesis result:\n";
    for (int i=0; i<result.size(); i++) std::cout << result[i] << std::endl;
}

/**
 * 23. 高楼仍鸡蛋
 * 方法1. 设dp[i,j]表示共i个鸡蛋，j层楼需要仍的次数；则dp[i,j]=min(max(dp[i-1,j-1],dp[i,j-k])+1) for k in [1,j]
 * 其中dp[i-1,k-1]表示在第k层仍，蛋碎了; dp[i, j-k]表示蛋没碎，剩下j-k层楼；
 * 注意初始化dp[i,0]=0, for(i=1->K, j=1->N; k->1->j)dp[i,j]加一时要判断是否超过表示范围。
 * 方法2: 根据dp[i-1][k]单调不减，dp[i][j-k]单调不增，可用二分法求得最中间的left,right
 * 最后直接dp[i,j]=min(max(dp[i-1][left-1], dp[i][j-left]), max(dp[i-1][right-1], dp[i][j-right])) + 1;
 * 方法3:定义新的更新状态dp[i,j]表示i个鸡蛋，仍j次，最多可用确定多高的楼层，则当dp[K,j]==N时，j即为结果
 * dp[i,j] = dp[i][m-1] + dp[i-1][m-1] + 1
 * 详见分析： https://leetcode-cn.com/problems/super-egg-drop/solution/ji-ben-dong-tai-gui-hua-jie-fa-by-labuladong/
*/
void test_superEggDrop() {
    int K = 2;
    int N = 6;
    int result = thot_50::superEggDrop_v3(K, N);
    std::cout << "test superEggDrop result: " << result << std::endl;
}


int main() {
    // test_minmum_depth_binary_tree();
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
    // test_is_palindrome();
    // test_maxPathSum();
    // test_maxprofix();
    // test_minimumTotal();
    // test_pascal_row();
    // test_populating_next_right_pointer();
    // test_min_distance_of_strintest_foursumg();
    // test_haspathsum();
    // test_qsort();
    // test_add_two_numbers();
    // test_length_of_substr();
    // test_find_mid_num();
    // test_length_palindrome();
    // test_z_convert();
    // test_my_atoi();
    // test_regular_match();
    // test_largest_rectangle_area();
    // test_maximal_square();
    // test_max_area_in_water_tank();
    // test_int_to_map();
    // test_is_subtree();
    // test_is_lowest_ancestor();
    // test_requent_tree_sum();
    // test_simple_path();
    // test_reverse_between();
    // test_juge_point24();
    // test_spiral_order();
    // test_generate_matrix();
    // test_match_idx_val();
    // test_mct_from_leaf();
    // test_three_sum();
    // test_advantage_count();
    // test_can_jump();
    // test_can_complete_circuit();
    // test_match_str();
    // test_remove_duplicate_letters();
    // test_max_sub_array();
    // test_unique_path(); 
    // test_unique_path_with_obstacle();
    // test_max_rectangle();
    // test_clone_graph2();
    // test_can_finish();
    // test_find_order();
    // test_find_highest_node();
    // test_letter_combination();
    // test_generate_parenthesis();
    // test_combination_sum();
    // test_dfs_isvalidtree();
    // test_recover_tree();
    // test_build_tree();
    // test_is_symmetric();
    // test_zigzag_level_order();
    // test_ladder_length_bfs();
    // test_eval_rpn();
    // test_trap();
    // test_find_k_largest();
    // test_merge_k_list();
    // test_divide();
    // test_search();
    // test_find_median_num();
    // test_merge_set();
    // test_num_island();
    // test_longest_consecutive2();
    // test_bi_node();
    // test_remove_nth_node();
    // test_length_substr();
    // test_unordered_map();
    // test_string();
    // test_str_longest_palindrome();
    // test_str_heap_topk();
    // test_dfs_bstTogst();
    // test_swap_pair();
    // test_min_window();
    // test_find_substr();
    // test_longest_valid_parentheses();
    // test_multiply();
    // test_longest_increaseing_path();
    // test_diving_board();
    // test_respace();
    // test_two_sum();
    // test_foursum();
    // test_subsets();
    // test_find_repeated_dnasequence();
    // test_lru();
    // test_maximum_gap();
    // test_mystack();
    // test_trie();
    // test_findword();
    // test_get_skyline();
    // test_numarray();
    // test_reverse_pairs();
    // test_can_win_nim();
    // test_get_menoy_account();
    // test_random_sample();
    // test_pick_target();
    // test_surface_area();
    // test_check_straightline();
    // test_min_time_visitedall();
    // test_inter_section();
    // test_max_sum_path();
    // test_sub_array_sum();
    // test_search_range();
    // test_queue();
    // test_permute();
    // test_next_permute();
    // test_combinationsum();
    // test_searchmatrix();
    // test_kthsmallest();
    // test_rotate_matrix();
    // test_groupAnagrams();
    // test_next_node();
    // test_myqueue();
    // test_mindistance(); 
    // test_simplepath();
    
    //***************sword finger offer ************************

    // test_print1ToNdigits();
    // test_deleteduplictednode();
    // test_regular_match_v2();
    // test_isNumeric();
    // test_reordervec();
    // test_detect_cycle();
    // test_reverse_list();
    // test_merge_two_list();
    // test_issubtree();
    // test_issymmetrical();test_longest_increasing_path
    // test_clockwise_print();
    // test_min_stack();
    // test_is_correct_for_stack();
    // test_z_print();
    // test_reverse();
    // test_check_bst_order();
    // test_sum_path();
    // test_bst2list();
    // test_serialize_deserialize();
    // test_permutation();
    // test_queen_permute();
    // test_morethanhalf();
    // test_topKminus();
    // test_median_number();
    // test_heap();
    // test_continuoussum();
    // test_one_counts();
    // test_number_of_digit();
    // test_mincombination();
    // test_number2ascii();
    // test_giftmaxval();
    // test_longest_substr();
    // test_ugly_number();
    // test_first_one_char();
    // test_count_reverse_pair();
    // test_common_node();
    // test_treenode_common_parent();
    // test_sorted_arr_count();
    // test_kthnode();
    // test_depthofBST();
    // test_balance_tree();
    // test_appearOnce();
    // test_appearOnce_of_three();
    // test_sum_of_s();
    // test_sum_of_s_v2();
    // test_reverse_str();
    // test_max_sequence();
    // test_probability_n();
    // test_is_continuous();
    // test_final_number();
    // test_maxprofit();
    // test_nsum();
    // test_sum_of_bits();test_longest_increasing_path
    // test_multipy();


    // ******************************** leetcode *********************************
    // test_topkFrequent();
    // test_h_index();
    // test_valid_parentness();
    // test_searchinsert();
    // test_merge_intervals();
    // test_minpathsum();
    // test_sort_color();
    // test_exist_board();
    // test_inorder_travel();
    // test_num_tree();
    // test_levelorder();
    // test_flatten();
    // test_max_profit();
    // test_tmp();
    // test_single_number();
    // test_wordBreak_simple();
    // test_detectcycle();

    // ***************************** hot 100 *************************************
    // test_findkthlargest_hot_100();
    // test_max_sliding_window_hot_100();
    // test_searchMatrix_hot_100();
    // test_numsquare_hot_100();
    // test_lengthofLIS_hot_100();
    // test_reconstruct_queue_hot_100();
    // test_pathsum_hot_100();
    // test_find_disappearedNumbers_hot_100();
    // test_daily_temperatures_hot_100();
    // test_max_profit_hot_100();
    // test_max_coins_hot_100();
    // test_find_unsorted_sub_array_hot_100();
    // test_rob();
    // test_count_bits();
    // test_decode_string();
    // test_can_partition();
    // test_leastInterval();
    // test_count_substring();

    // ******************************** thot 50 *************************************
    // test_longest_increasing_path();
    // test_reverse_thot50();
    // test_permute_thot50();
    // test_subset_thot50();
    // test_generate_parenthesis_thot50();
    test_superEggDrop();

    return 0;
}
