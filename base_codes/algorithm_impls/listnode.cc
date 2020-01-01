#include <set>
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

    ListNode* merge_list_simple(ListNode* list1, ListNode* list2) {
        ListNode root_node = ListNode(-1);
        ListNode* root = &root_node;
        ListNode* root_ptr = root;
        ListNode* list1_ptr = list1;
        ListNode* list2_ptr = list2;
        while (list1_ptr != NULL && list2_ptr != NULL) {
            root_ptr->next = list1_ptr;
            ListNode* tmp = list1_ptr;
            list1_ptr = list1_ptr->next;
            tmp->next = list2_ptr;
            tmp = list2_ptr;
            list2_ptr = list2_ptr->next;
            root_ptr = tmp;
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

    ListNode* reverseList(ListNode* head) {
        ListNode root_node = ListNode(-1);
        ListNode* root = &root_node;
        ListNode* head_copy = head;
        while(head_copy != NULL) {
            ListNode* tmp = root->next;
            root->next = head_copy;
            head_copy = head_copy->next;
            root->next->next = tmp;
        }
        return root->next;
    }

    ListNode* reorderList_V2(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* midnode_ptr = getmid(head);
        ListNode* reversed_ptr = reverseList(midnode_ptr);
        // merge to list
        ListNode root_node = ListNode(-1);
        ListNode* root = &root_node;
        ListNode* root_ptr = root;
        ListNode* head_ptr = head;
        return merge_list_simple(head_ptr, reversed_ptr);
    }

    ListNode* detectCycle(ListNode* head) {
        ListNode* head_ptr = head;
        if (head == NULL || head->next == NULL) return NULL;
        std::set<ListNode*> node_sets;
        while(head_ptr != NULL) {
            if (node_sets.find(head_ptr) != node_sets.end()) {
                return head_ptr;
            }
            else {
                node_sets.insert(head_ptr);
            }
            head_ptr = head_ptr->next;
        }
        return NULL;
    }

    ListNode* isCycle(ListNode* head) {
        ListNode* one = head;
        ListNode* two = head;
        while(two != NULL && two->next != NULL) {
            one = one->next;
            two = two->next->next;
            if (one == two) return one;
        }
        return NULL;
    }

    ListNode* detectCycle_V2(ListNode* head) {
        if (head == NULL || head->next == NULL) return NULL;
        ListNode* head_ptr = head;
        ListNode* mid_ptr = isCycle(head_ptr);
        if (mid_ptr != NULL) {
            while(head_ptr != mid_ptr) {
                head_ptr = head_ptr->next;
                mid_ptr = mid_ptr->next;
            }
            return head_ptr;
        }
        return NULL;
    }

    RandomListNode* copyRandomList(RandomListNode* head) {
        if (head == NULL) return NULL;
        RandomListNode* copy, *p;
        p = head;
        // copy ListNode follow each node
        while(p != NULL) {
            copy = new RandomListNode(p->label);
            copy->next = p->next;
            p->next = copy;
            p = copy->next;
        }
        p = head;
        // set random pointer
        while (p != NULL) {
            copy = p->next;
            copy->random = p->random?p->random->next:NULL;
            p=copy->next;
        }
        // split the two RandomListNode
        p = head;
        RandomListNode* copy_head = head->next;
        copy = copy_head;
        while(copy->next != NULL) {  // not copy != NULL
            p->next = copy->next;
            p = p->next;
            copy->next = p->next;
            copy = copy->next;
        }
        p->next = NULL;
        return copy_head;
    }
}