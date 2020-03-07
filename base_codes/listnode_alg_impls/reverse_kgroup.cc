#include "../listnode_algs.h"


ListNode* listnode_alg::reverse_listnode(ListNode* pre, ListNode* end) {
    if (pre==nullptr||pre->next==nullptr||pre->next==end) return pre->next;
    ListNode* end_next = end->next;
    ListNode* curr = pre->next->next;
    ListNode* new_end = pre->next;
    new_end->next = nullptr;
    while(curr!=end_next) {
        ListNode* curr_next = curr->next;
        curr->next = pre->next;
        pre->next=curr;
        curr = curr_next;
    }
    return new_end;
}

ListNode* listnode_alg::reverseKGroup(ListNode* head, int k) {
    if (k==1) return head;
    ListNode* prenode = new ListNode(-1);
    prenode->next = head;
    ListNode* pre = prenode;
    ListNode* curr = head;
    int count = 0;
    while(curr!=nullptr) {
        count++;
        if (count%k==0) {
            ListNode* curr_next = curr->next;
            ListNode* curr_end = reverse_listnode(pre, curr);
            curr_end->next = curr_next;
            pre = curr_end;
            curr = curr_next;
        }
        else {
            curr=curr->next;
        }
    }

    ListNode* new_head = prenode->next;
    delete prenode;
    return new_head;
}