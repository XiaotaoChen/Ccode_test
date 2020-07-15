#include <string>
#include <vector>
#include <iostream>
#include "./algorithms.h"
#include "./base_struct.h"

struct point
{
    int x, y;
    point():x(0), y(0){}
    point(int a, int b):x(a), y(b){}
    void print() {
        printf("point:(%d, %d)\n", x, y);
    }
};

/**
 * 路径总和
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
void test_pathsum() {
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
    int result = algorithms::pathSum(root, target);
    std::cout << "test pathsum result: " << result << std::endl;
}

/**
 * 2. 三角形最小路径和
*/
void test_minimum_total() {
    std::vector<std::vector<int> > triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    int result = algorithms::minimumTotal(triangle);
    std::cout << "test minimum total result: " << result << std::endl;
}

/**
 * 3. 合并两个排序链表
*/
void test_merge_two_list() {
    ListNode* root = new ListNode(1);
    root->next = new ListNode(2);
    root->next->next = new ListNode(4);
    ListNode* root2 = new ListNode(1);
    root2->next = new ListNode(3);
    root2->next->next = new ListNode(4);
    ListNode* head = algorithms::mergeTwoLists(root, root2);
    std::cout << "test merge two list result: ";
    while(head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

/**
 * 4. 二叉树等最大深度
*/
void test_max_depth() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    int depth = algorithms::maxDepth(root);
    std::cout << "test max depth result: "<< depth << std::endl;
}

/**
 * 5. LRU 设计
*/
void test_lru_cache() {
    int val;
    algorithms::LRUCache cache = algorithms::LRUCache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    val = cache.get(1);       // 返回  1
    std::cout << "get 1 value: "<< val << std::endl;
    cache.put(3, 3);    // 该操作会使得关键字 2 作废
    val = cache.get(2);       // 返回 -1 (未找到)
    std::cout << "get 2 value: "<< val << std::endl;
    cache.put(4, 4);    // 该操作会使得关键字 1 作废
    val = cache.get(1);       // 返回 -1 (未找到)
    std::cout << "get 1 value: "<< val << std::endl;
    val = cache.get(3);       // 返回  3
    std::cout << "get 3 value: "<< val << std::endl;
    val = cache.get(4);       // 返回  4
    std::cout << "get 4 value: "<< val << std::endl;
}

/**
 * 6. 最大连续子数组乘积
 * dp[i]表示0到i到数组中，包含i个元素到子数组乘积。要分别记录最大，最小乘积。
*/
void test_max_product() {
    std::vector<int> nums = {-2,0,-1}; //{2,3,-2,4};
    int result = algorithms::maxProduct(nums);
    std::cout << "test max product result: " << result << std::endl;
}

/**
 * 7. 排序链表
*/
void test_sort_list() {
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);
    ListNode* sortedhead = algorithms::sortList(head);
    std::cout << "test sort list result: ";
    while(sortedhead!=nullptr) {
        std::cout << sortedhead->val << " ";
        sortedhead = sortedhead->next;
    }
    std::cout << std::endl;
}

int main() {
    // point p1 = point(1,2);
    // p1.print();

    // test_pathsum();
    // test_minimum_total();
    // test_merge_two_list();
    // test_max_depth();
    // test_lru_cache();
    // test_max_product();
    test_sort_list();

    return 0;
}
