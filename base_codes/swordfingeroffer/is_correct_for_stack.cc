#include <vector>
#include <map>
#include <stack>

#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool is_correct_for_stack(std::vector<int>& instack, std::vector<int>& outstack) {
    if (instack.size() == 0 && outstack.size() == 0)  return true;
    if (instack.size() != outstack.size()) return false;
    std::stack<int> s;

    int push_idx = 0;
    for (int i=0; i<outstack.size(); i++) {
        if (!s.empty() && s.top() == outstack[i]) {
            s.pop();
            continue;
        }
        bool is_correct = false;
        while(push_idx < instack.size()) {
            s.push(instack[push_idx]);
            push_idx++;
            if (instack[push_idx-1] == outstack[i]) {
                s.pop();
                is_correct = true;
                break;
            }
        }
        if (!is_correct) return false;
    }
    return true;
}

} // namespace sword_finger_offer
