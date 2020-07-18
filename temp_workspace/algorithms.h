#ifndef ALGORITHM_IMPLS
#define ALGORITHM_IMPLS

#include <vector>
#include <climits>
#include <algorithm>
#include <list>
#include <unordered_map>
#include "./base_struct.h"

namespace algorithms
{
// https://leetcode-cn.com/problems/path-sum-iii/
int pathSum(TreeNode* root, int sum);

// https://leetcode-cn.com/problems/triangle/
int minimumTotal(std::vector<std::vector<int> >& triangle);

// https://leetcode-cn.com/problems/merge-two-sorted-lists/
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);

// https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
int maxDepth(TreeNode* root);

class LRUCache {
public:
    LRUCache():capacity(10){}
    LRUCache(int capacity): capacity(capacity){}
    int get(int key);
    void put(int key, int value);

private:
    int capacity;
    std::list<std::pair<int, int> > list;
    std::unordered_map<int, std::list<std::pair<int,int> >::iterator > mp;

};

// https://leetcode-cn.com/problems/maximum-product-subarray/
int maxProduct(std::vector<int>& nums);

// https://leetcode-cn.com/problems/sort-list/
ListNode* sortList(ListNode* head);

// https://leetcode-cn.com/problems/invert-binary-tree/
TreeNode* invertTree(TreeNode* root);

// https://leetcode-cn.com/problems/palindrome-linked-list/
bool isPalindrome(ListNode* head);

} // namespace algorithms


#endif