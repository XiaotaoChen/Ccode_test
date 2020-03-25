#include <cstdlib>
#include "../random_sample_algs.h"

namespace random_sample_alg
{

Solution::Solution(ListNode* head): root(head) {
    // std::srand(0);
}

/** Returns a random node's value. */
int Solution::getRandom() {
    if (root ==nullptr) return -1;

    int result = -1;
    ListNode* curr = root;
    int count = 0;
    while(curr != nullptr) {
        count++;
        int random_val = std::rand()%count;
        if (random_val==(count-1)) {
            result = curr->val;
        }
        curr = curr->next;
    }
    return result;
}

} // namespace random_sample_alg
