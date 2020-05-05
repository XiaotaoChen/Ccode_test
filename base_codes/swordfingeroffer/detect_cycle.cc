#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

ListNode* detectCycle(ListNode* root) {
    if (root == nullptr || root->next == nullptr) return nullptr;
    ListNode* prehead = new ListNode(-1);
    prehead->next = root;
    ListNode* slow = prehead;
    ListNode* fast = prehead;
    
    // detect cycle
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (slow != fast) return nullptr;

    // to find the begining node
    slow = prehead;
    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    delete prehead;
    return slow;
}

} // namespace sword_finger_offer
