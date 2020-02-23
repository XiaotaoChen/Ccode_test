#include <cstdio>
#include <vector>
#include "../search_algs.h"

bool search::isSametree(TreeNode* s, TreeNode* t) {
    if (s == nullptr && t == nullptr) return true;
    if (s != nullptr && t != nullptr && s->val == t->val) {
        return isSametree(s->left, t->left) && isSametree(s->right, t->right);
    }
    return false;
}

bool search::isSubtree(TreeNode* s, TreeNode* t) {
    if (s == nullptr && t == nullptr) return true;
    if (s == nullptr && t != nullptr) return false;
    if (s != nullptr && t == nullptr) return false;
    if (s->val == t->val) {
        // return (isSametree(s->left, t->left) && isSametree(s->right, t->right));
        return (isSametree(s->left, t->left) && isSametree(s->right, t->right)) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    else {
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
}