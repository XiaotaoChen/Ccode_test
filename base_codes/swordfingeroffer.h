#ifndef SWORD_FINGER_OFFER_
#define SWORD_FINGER_OFFER_
#include <string>
#include <vector>
#include <stack>
#include "./data_structs/base_struct.h"
#include "./data_structs/base_struct.h"

namespace sword_finger_offer
{

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

} // namespace sword_finger_offer


#endif