#include <cstdio>

#include "../search_algs.h"
#include "../data_structs/base_struct.h"


ListNode* search::addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr)  return l2;
    if (l2 == nullptr) return l1;
    
    ListNode *l1_curr = l1;
    ListNode *l2_curr = l2;
    ListNode  *head = new ListNode(-1);
    ListNode *curr = head;
    while(l1_curr != nullptr && l2_curr != nullptr) {
        curr->next = new ListNode(l1_curr->val + l2_curr->val);
        curr = curr->next;
        l1_curr = l1_curr->next;
        l2_curr = l2_curr->next;
    }
    if (l1_curr != nullptr) {
        curr->next = l1_curr;
    }
    else if (l2_curr != nullptr) {
        curr->next = l2_curr;
    }
    // convert to normal number
    curr = head->next;
    while(curr != nullptr && curr->next != nullptr) {
        curr->next->val += curr->val / 10;
        curr->val = curr->val %10;
        curr = curr->next;
    }
    if (curr->val>=10) {
        curr->next = new ListNode(curr->val / 10);
        curr->val %= 10;
    }
    return head->next;
}

ListNode* search::addTwoNumbers_v2(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr)  return l2;
    if (l2 == nullptr) return l1;
    
    ListNode *l1_curr = l1;
    ListNode *l2_curr = l2;
    ListNode  *head = new ListNode(-1);
    ListNode *curr = head;
    int carry = 0;
    while(l1_curr != nullptr && l2_curr != nullptr) {
        curr->next = new ListNode((l1_curr->val + l2_curr->val + carry) % 10);
        carry = (l1_curr->val + l2_curr->val + carry) / 10;
        curr = curr->next;
        l1_curr = l1_curr->next;
        l2_curr = l2_curr->next;
    }
    if (l1_curr != nullptr) {
        curr->next = l1_curr;
    }
    else if (l2_curr != nullptr) {
        curr->next = l2_curr;
    }
    if (carry == 0) return head->next;
    while(curr != nullptr && carry != 0) {
        if (curr->next != nullptr) {
            int tmp = curr->next->val + carry;
            curr->next->val = tmp % 10;
            carry = tmp / 10;
        }
        else {
            curr->next = new ListNode(carry);
            carry = 0;
        }
        curr = curr->next;
    }

    return head->next;
}