#ifndef LISTNODE_ALG_
#define LISTNODE_ALG_

#include "data_structs/base_struct.h"

namespace listnode_alg {

//  https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
ListNode* removeNthFromEnd(ListNode* head, int n);

// https://leetcode-cn.com/problems/swap-nodes-in-pairs/
ListNode* swapPairs(ListNode* head);

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/
/*
    １．　注意传入函数的指针已经被修改．
    ２．　reverse listnode ：反序一个list, 从pre->next到end. 其返回反序后的列表的最后一个节点．因为最后一个节点的next指针需要额外设置．
*/
ListNode* reverseKGroup(ListNode* head, int k);
ListNode* reverse_listnode(ListNode* pre, ListNode* end);


// https://leetcode-cn.com/problems/linked-list-cycle-ii/
ListNode *detectCycle(ListNode *head);
}

#endif