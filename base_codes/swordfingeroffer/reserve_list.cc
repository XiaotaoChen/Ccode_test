#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

ListNode* reverseList(ListNode* root) {
    if (root == nullptr || root->next == nullptr) return root;
    ListNode* prehead = new ListNode(-1);
    ListNode* pre = root;
    ListNode* curr = root;
    while(curr != nullptr) {
        pre = curr;
        curr = curr->next;

        pre->next = prehead->next;
        prehead->next = pre;
    }
    delete prehead;
    return pre;
}

} // namespace sword_finger_offer
