#include "../binary_search.h"

namespace binary_search
{

TreeLinkNode* next_node(TreeLinkNode* node) {
    if (node == nullptr) return node;
    if (node->right != nullptr) return node->right;
    TreeLinkNode* curr = node;
    TreeLinkNode* parent = node->next;
    while(parent != nullptr && parent->right == curr) {
        curr = parent;
        parent = parent->next;
    }
    return parent;
}

} // namespace binary_search
