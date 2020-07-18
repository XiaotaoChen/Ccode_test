#include "../base_struct.h"
#include "../algorithms.h"

namespace algorithms
{

bool isPalindrome(ListNode* head) {
    if (head==nullptr || head->next==nullptr) return true;
    // get mid ptr
    ListNode* one = head;
    ListNode* two = head->next;
    while(two!=nullptr&&two->next!=nullptr) {
        one = one->next;
        two = two->next->next;
    }
    ListNode* mid_pre = one;
    ListNode* curr = one->next;
    ListNode* next = curr->next;
    curr->next = nullptr;
    curr=next;
    while(curr!=nullptr) {
        next = curr->next;
        curr->next = mid_pre->next;
        mid_pre->next = curr;
        curr=next;
    }
    ListNode* head1 = head;
    ListNode* head2 = mid_pre->next;
    while(head1!=nullptr && head2!=nullptr) {
        if (head1->val!=head2->val) return false;
        head1 = head1->next;
        head2 = head2->next;
    }
    return true;
}

} // namespace algorithms
