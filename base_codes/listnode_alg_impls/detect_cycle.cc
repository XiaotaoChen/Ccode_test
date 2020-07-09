#include "../data_structs/base_struct.h"
#include "../listnode_algs.h"

namespace listnode_alg
{

ListNode* detectCycle(ListNode *head) {
    if (head == nullptr||head->next==nullptr) return nullptr;
    ListNode* one = head;
    ListNode* two = head;
    while(two!=nullptr&& two->next!=nullptr) {
        one = one->next;
        two = two->next->next;
        if (one == two) {
            break;
        }
    }
    if (one!=two) return nullptr;
    one = head;
    while(one != two) {
        one = one->next;
        two = two->next;
    }
    return two;
}

} // namespace listnode_alg
