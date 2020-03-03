#include <vector>

#include "../heap_algs.h"

ListNode* heap::meregeTwoList(ListNode* root1, ListNode* root2) {
    if (root1==nullptr) return root2;
    if (root2==nullptr) return root1;
    ListNode* head = new ListNode(-1);
    ListNode* curr = head;

    while(root1!=nullptr && root2!=nullptr) {
        if (root1->val < root2->val) {
            curr->next = root1;
            root1 = root1->next;
        }
        else {
            curr->next = root2;
            root2 = root2->next;
        }
        curr = curr->next;
    }
    if (root1==nullptr) {
        curr->next = root2;
    }
    else {
        curr->next = root1;
    }
    curr = head->next;
    delete head;
    return curr;
}

ListNode* heap::mergeKLists(std::vector<ListNode*>& lists, int start, int end) {
    if (start == end) return lists[start];
    if (end - start == 1) {
        return meregeTwoList(lists[start], lists[end]);
    }
    else {
        int mid = (start + end) /2;
        ListNode* root1 = mergeKLists(lists, start, mid);
        ListNode* root2 = mergeKLists(lists, mid+1, end);
        return meregeTwoList(root1, root2);
    }
        
}

ListNode* heap::mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.size()==0) return nullptr;
    return mergeKLists(lists, 0, lists.size()-1);
}