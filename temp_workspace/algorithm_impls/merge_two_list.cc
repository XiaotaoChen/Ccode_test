#include "../base_struct.h"
#include "../algorithms.h"

namespace algorithms
{

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode* head = new ListNode(-1);
    ListNode* pre = head;
    while(l1!=nullptr && l2!=nullptr) {
        if (l1->val < l2->val) {
            pre->next = l1;
            l1 = l1->next;
        }
        else {
            pre->next = l2;
            l2 = l2->next;
        }
        pre = pre->next;
    }
    if(l1!=nullptr) pre->next = l1;
    if (l2!=nullptr) pre->next = l2;
    ListNode* root = head->next;
    delete head;
    return root;
}

} // namespace algorithms
