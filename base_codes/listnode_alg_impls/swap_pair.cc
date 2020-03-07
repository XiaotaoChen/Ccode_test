#include "../listnode_algs.h"

ListNode* listnode_alg::swapPairs(ListNode* head) {
    if (head==nullptr||head->next==nullptr) return head;

    ListNode* prenode = new ListNode(-1);
    prenode->next = head;
    ListNode* pre = prenode;

    ListNode* curr = head;
    while(curr!=nullptr && curr->next!=nullptr) {
        ListNode* curr_next = curr->next;
        curr->next = curr_next->next;
        curr_next->next = curr;
        pre->next = curr_next;
        
        pre = curr;
        curr = curr->next;
    }

    ListNode* new_head = prenode->next;
    delete prenode;
    return new_head;
}