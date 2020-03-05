
#include "../listnode_algs.h"

ListNode* listnode_alg::removeNthFromEnd(ListNode* head, int n) {
    int count=0;
    ListNode* curr_n = head;
    while(curr_n!=nullptr && count <n) {
        curr_n = curr_n->next;
        count++;
    }
    if (count<n) return head;
    ListNode* prenode = new ListNode(-1);
    prenode->next = head;
    ListNode* pre = prenode;
    ListNode* curr = head;
    while(curr_n!=nullptr) {
        pre = curr;
        curr = curr->next;
        curr_n = curr_n->next;
    }
    // to delete curr
    pre->next = curr->next;
    head = prenode->next;
    delete prenode;
    return head;
}