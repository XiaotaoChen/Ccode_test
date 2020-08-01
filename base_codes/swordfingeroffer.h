#ifndef SWORD_FINGER_OFFER_
#define SWORD_FINGER_OFFER_
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <string>
#include <unordered_map>
#include "./data_structs/base_struct.h"
#include "./data_structs/base_struct.h"

namespace sword_finger_offer
{

template<typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// interview 17 打印１到ｎ位最大数的所有可能
void print1ToMaxNDigits(int n);

bool increment(char* member);

bool PrintNumber(char* member);

void print1ToMaxNDigits_v2(int n);
void print_dfs(char* member, int depth, int n);

// interview 18 删除链表中连续重复的节点
void deleteDuplicatedNode(ListNode** root);

// interview 19 正则表达式
bool regular_pattern(std::string& str, std::string& pattern);
bool match_core(std::string& str, int index, std::string& pattern, int p_index);

// interview 20 判断字符串是不是合法数字
bool isNumeric(std::string& s);

bool scanInteger(std::string& s, int& index);

bool scanUnsignedInteger(std::string& s, int& index);

// interview 21 区分奇偶数，抽象判断条件
void reorderVec(std::vector<int>& vec, bool(*func)(int));

// interview 23 检测链表中是否存在环，并找出环的入口
ListNode* detectCycle(ListNode* root);

// interview 24 反转链表
ListNode* reverseList(ListNode* root);

// interview 25 合并两个排序链表
ListNode* mergetwoList(ListNode* root1, ListNode* root2);
ListNode* mergetwoList_v2(ListNode* root1, ListNode* root2);

// interview 26 subtree

bool issametree(TreeNode* root1, TreeNode* root2);
bool issubtree(TreeNode* root1, TreeNode* root2);

// interview 28 判断二叉树是否对称
bool isSymmetrical(TreeNode* root);
bool isSymmetrical(TreeNode* root1, TreeNode* root2);

// interview 29 顺时针打印
void clockwise_print(std::vector<std::vector<int>>& matrix);

// interview 30 min stack
template<typename T>
class minStack {
private:
    std::stack<T> my_stack;
    std::stack<T> min_stack;
public:
    void push(const T& element) {
        if (my_stack.empty()) {
            my_stack.push(element);
            min_stack.push(element);
        }
        else {
            my_stack.push(element);
            if (element >= min_stack.top()) min_stack.push(min_stack.top());
            else min_stack.push(element);
        }
    }
    void pop() {
        if (my_stack.empty()) return;
        my_stack.pop();
        min_stack.pop();
    }

    bool min(T& element) {
        if (my_stack.empty()) return false;
        element = min_stack.top();
        return true;
    }
};

// interview 31 判断入栈，出栈序列是否合法
bool is_correct_for_stack(std::vector<int>& instack, std::vector<int>& outstack);

// interview 32 z字形打印二叉树
void print_binary_tree_with_z(TreeNode* root) ;

void print_binary_tree_with_z_v2(TreeNode* root) ;

bool check_binary_search_tree_order(std::vector<int>& vec);

bool check_bst_dfs(std::vector<int>& vec, int begin, int end);

std::vector<std::vector<int>> sum_path(TreeNode* root, int target);

void sum_path_dfs(std::vector<std::vector<int>>& commbinations, std::vector<int> curr, TreeNode* root, int target);

void sum_path_v2(TreeNode* root, int target);
void sum_path_dfs_v2(std::vector<int> curr, TreeNode* root, int target);

// interview 36 二叉树转换成双向链表
void bst2list(TreeNode* root, TreeNode** last);
TreeNode* get_list_head(TreeNode* root);

// interview 37 二叉树序列化，反序列化
std::string serialize(TreeNode* root);
void serialize_dfs(TreeNode* root, std::string& oss);
TreeNode* deserialize(std::string& oss);
void deserialize_dfs(std::string& oss, TreeNode* root, int index);

void print_bst(TreeNode* root);

void serialize_ss(TreeNode* root, std::ostream& oss);
void deserialize_ss(TreeNode** root, std::istream& iss);

// interview 38 生成排列组合
std::vector<std::string> permutation(std::string str);

std::vector<std::string> combinations(std::string str);

std::vector<std::vector<int>> queen_permutation(int num);


int partition(std::vector<int>& arr, int begin, int end);

// interview 39 出现次数超过一半的数
int MoreThanHalf(std::vector<int>& arr);

// interview 40 最小的ｋ个数
std::vector<int> TopKminus(std::vector<int>& arr, int k);
std::vector<int> TopKminus_with_heap(std::vector<int>& arr, int k);
std::vector<int> TopKminus_with_makeheap(std::vector<int>& arr, int k);
std::vector<int> TopKminus_with_set(std::vector<int>& arr, int k);

// interview 41 流数据的中位数
int median_number(std::vector<int>& arr);
int median_number_with_set(std::vector<int>& arr);

float median_number_V2(std::vector<int>& arr);
float median_number_V3(std::vector<int>& arr);


// interview 42 连续子数组的最大和
int continuoussum(std::vector<int>& arr);

// interview 43 连续数字，１出现的次数
int one_counts(int n);

// interview 44 数字序列中第ｎ位的数字
int numberofindex(int index);

// interview 45　得到数字组合的最小值
std::string mincombination(std::vector<int>& arr);


// interview 46 数字转换成字母
int number2ascii(int num);

// interview 47 礼物最大价值
int giftmaxval(std::vector<std::vector<int>>& gifts);

// interview 48 最长不重复的子字符串
int longest_substr(std::string str);
int longest_substr_v2(std::string str);

// interview 49 丑数
int ugly_number(int index);

// interview 50 第一次只出现一次的字符
char first_one_char(std::string& str);
char first_one_char_v2(std::string& str);
char first_one_char_v3(std::string& str);

// interview 51 逆序对个数
int count_reverse_pair(std::vector<int>& arr);

// interview 52 链表中第一个公共节点
ListNode* first_common_node(ListNode* root1, ListNode* root2);

TreeNode* lastest_common_parent(TreeNode* root, TreeNode* node1, TreeNode* node2);

// interview 53 找出排序数组中某个数字的个数
int sorted_arr_count(std::vector<int>& arr, int num);
int sorted_arr_count_v2(std::vector<int>& arr, int num);

// interview 54 第k大的节点
TreeNode* kthNode(TreeNode* root, int k);

// interview 55 二叉树的深度
int depthOfTreeNode(TreeNode* root);
int depthOfTreeNode_v2(TreeNode* root);

bool check_balance_tree(TreeNode* root);

// interview 56 数组中出现的1次数的两个数字
std::pair<int, int> appearOnce(std::vector<int>& arr);
int appearOnce_of_three(std::vector<int>& arr);
int appearOnce_of_three_v2(std::vector<int>& arr);


// interview 57 找出排序数组中和为s,的两个数
std::pair<int, int> sum_of_s(std::vector<int>& arr, int s);
std::vector<std::vector<int>> sum_of_s_v2(int num);

// interview 58 翻转字符串
std::string reverse_str(std::string& str);

// interview 59 队列的最大值
std::vector<int> max_sequence(std::vector<int>& arr, int windows);
std::vector<int> max_sequence_v2(std::vector<int>& arr, int windows);

std::vector<int> max_sequence_v3(std::vector<int>& arr, int windows);
std::vector<int> max_sequence_v4(std::vector<int>& arr, int windows);

// interview 60 n个骰子的点数
std::unordered_map<int, float> probability_n(int n);

// interview 61 扑克牌中的顺子
bool isContinuous(std::vector<int>& arr);

// interview 62 圆圈中最后剩下的数字
int finalNumber(int n, int m);
int finalNumber_v2(int n, int m);

// interview 63 股票的最大利润
int maxprofit(std::vector<int>& arr);

// interview 64 1+2+...+n 的结果，　不使用乘除法，ｉf, for等
int nsum(int n);

// interview 65 不用加减乘除做加法
int sum_in_bits(int num1, int num2);

// interview 66 不用除法，求A[0...n-1]/A[i]
std::vector<int> multipy(std::vector<int>& arr);

} // namespace sword_finger_offer


#endif
