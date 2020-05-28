#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

int get_length(ListNode* root) {
    int len = 0;
    ListNode* head = root;
    while(head !=nullptr) {
        len++;
        head = head->next;
    }
    return len;
}

ListNode* first_common_node(ListNode* root1, ListNode* root2) {
    if (root1==nullptr || root2==nullptr) return nullptr;
    int len1 = get_length(root1);
    int len2 = get_length(root2);
    ListNode *head1 = root1;
    ListNode* head2 = root2;
    if (len1 > len2) {
        for (int i=0; i<len1-len2; i++) head1 = head1->next;
    }
    else {
        for (int i=0; i<len2-len1; i++) head2 = head2->next;
    }
    while(head1!=nullptr) {
        if (head1 == head2) return head1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return nullptr;
}

TreeNode* lastest_common_parent(TreeNode* root, TreeNode* node1, TreeNode* node2) {
    if (root==nullptr|| node1==nullptr || node2 == nullptr) return nullptr;
    if (root == node1 || root == node2) return root;
    TreeNode* root1 = lastest_common_parent(root->left, node1, node2);
    TreeNode* root2 = lastest_common_parent(root->right, node1, node2);
    if (root1==nullptr && root2 == nullptr) return nullptr;
    if (root1==nullptr) return root2;
    if (root2==nullptr) return root1;
    return root;
}

} // namespace sword_finger_offer
