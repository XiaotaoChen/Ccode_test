#include <cstdio>

#include "../search_algs.h"

ListNode* search::reverseBetween(ListNode* head, int m, int n) {
    if (m==n) return head;
    ListNode* pre_m = nullptr;
    ListNode* m_node = nullptr;
    ListNode* tmp_curr = nullptr;
    ListNode* new_head = new ListNode(-1);
    new_head->next = head;
    ListNode* curr = new_head;
    int num = -1;
    while(curr != nullptr) {
        num ++;
        tmp_curr = curr;
        curr = curr->next;
        if (num == m-1) {
            pre_m = tmp_curr;
            m_node = curr;
        }
        // to avoid m == n
        // else if (num == m) {
        //     m_node->next = nullptr;
        // }
        else if (num >m && num <n) {
            tmp_curr->next = pre_m->next;
            pre_m->next = tmp_curr;
        }
        else if (num == n) {
            tmp_curr->next = pre_m->next;
            pre_m->next = tmp_curr;
            m_node->next = curr;
        }
    }
    return new_head->next;
}