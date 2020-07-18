#include "../base_struct.h"
#include "../algorithms.h"

namespace algorithms
{

ListNode* sortList_dfs(ListNode* head) {
    if (head==nullptr || head->next == nullptr) return head;
    //快慢指针寻找中点
    ListNode* one = head;
    ListNode* two = head->next;
    while(two!=nullptr && two->next!=nullptr) {
        one = one->next;
        two = two->next->next;
    }
    ListNode* mid_head = one->next;
    one->next = nullptr;

    ListNode* begin_head = sortList_dfs(head);
    mid_head = sortList_dfs(mid_head);

    ListNode* pre_node = new ListNode(-1);
    ListNode* curr = pre_node;

    while(begin_head!=nullptr && mid_head!=nullptr) {
        if (begin_head->val < mid_head->val) {
            curr->next = begin_head;
            begin_head = begin_head->next;
        }
        else {
            curr->next = mid_head;
            mid_head = mid_head->next;
        }
        curr = curr->next;
    }
    if (begin_head!=nullptr) curr->next = begin_head;
    if (mid_head!=nullptr) curr->next = mid_head;
    ListNode* sorted_head = pre_node->next;
    delete pre_node;
    return sorted_head;
}

ListNode* sortList(ListNode* head) {
    return sortList_dfs(head);
}

} // namespace algorithms
