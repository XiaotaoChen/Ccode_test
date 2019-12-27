#include "../algorithm.h"

namespace list_node {
    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* mid_ptr = getmid(head);
        ListNode* sorted_list1 = sortList(head);
        ListNode* sorted_list2 = sortList(mid_ptr);
        head = merge_list(sorted_list1, sorted_list2);
        return head;
    }

    ListNode* getmid(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* one = head;
        ListNode* two = head;
        ListNode* pre_one = one;
        while(two != NULL && two->next !=NULL) {
            pre_one = one;
            one = one->next;
            two = two->next->next;
        }
        pre_one->next = NULL;
        return one;
    }

    ListNode* merge_list(ListNode* list1, ListNode* list2) {
        ListNode head_node = ListNode(-1);
        ListNode* root = &head_node;
        ListNode* curr = root;
        while(list1 != NULL && list2 != NULL) {
            if (list1->val <= list2->val) {
                curr->next = list1;
                curr = curr->next;
                list1 = list1->next;
            }
            else {
                curr->next = list2;
                curr = curr->next;
                list2 = list2->next;
            }
        }
        if (list1 != NULL) {
            curr->next = list1;
        } 
        else {
            curr->next = list2;
        }
        return root->next;
    }

    ListNode* insertSortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode root_node = ListNode(-1);
        ListNode* root = &root_node;
        root->next = head;
        head = head->next;
        root->next->next = NULL;
        while(head != NULL) {
            ListNode* tmp = head;
            head = head->next;
            ListNode* curr = root->next;
            ListNode* pre = root;
            while(curr != NULL) {
                if (curr->val > tmp->val) break;
                pre = curr;
                curr = curr->next;
            }
            pre->next = tmp;
            tmp->next = curr;
        }
        return root->next;
    }
}