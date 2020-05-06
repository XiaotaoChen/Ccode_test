#include "../data_structs/base_struct.h"
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

ListNode* mergetwoList(ListNode* root1, ListNode* root2) {
    if (root1 == nullptr) return root2;
    if (root2 == nullptr) return root1;

    ListNode* prehead = new ListNode(-1);
    ListNode* curr = prehead;
    ListNode* curr1 = root1;
    ListNode* curr2 = root2;
    while(curr1 != nullptr && curr2 != nullptr) {
        if (curr1->val <= curr2->val) {
            curr->next = curr1;
            curr = curr->next;

            curr1 = curr1->next;
        }
        else {
            curr->next = curr2;
            curr = curr->next;
            
            curr2 = curr2->next;
        }
    }
    if (curr1 != nullptr) curr->next = curr1;
    if (curr2 != nullptr) curr->next = curr2;

    curr = prehead->next;
    delete prehead;
    return curr;
}

ListNode* mergetwoList_v2(ListNode* root1, ListNode* root2) {
    if (root1 == nullptr) return root2;
    if (root2 == nullptr) return root1;
    ListNode* head = nullptr;

    if (root1->val <= root2->val) {
        head = root1;
        head->next = mergetwoList_v2(root1->next, root2);
    }
    else {
        head = root2;
        head->next = mergetwoList_v2(root1, root2->next);
    }
    return head;
}

} // namespace sword_finger_offer
