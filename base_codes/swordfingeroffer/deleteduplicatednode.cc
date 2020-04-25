#include "../swordfingeroffer.h"
#include "../data_structs/base_struct.h"

namespace sword_finger_offer
{

void deleteDuplicatedNode(ListNode** root) {
    ListNode* head = *root;
    if (head == nullptr || head->next==nullptr)  return ;
    ListNode* prehead = head;
    ListNode* curr = prehead->next;
    while(curr != nullptr) {
        if (prehead->val == curr->val) {
            curr = curr->next;
            delete prehead->next;
            prehead->next = curr;
        }
        else {
            prehead = curr;
            curr = curr->next;
        }
    }
}

} // namespace sword_finger_offer
