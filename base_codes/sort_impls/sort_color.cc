#include <vector>
#include "../sorts.h"

namespace sort
{

void sortColors(std::vector<int>& nums) {
    if (nums.size()<=1) return ;
    int index2 = nums.size();
    int index0 = -1;
    while(index0+1 < nums.size() && nums[index0+1]==0) index0++;
    while(index2>0 && index2-1 < nums.size() && nums[index2-1]==2) index2--;
    int curr = index0 + 1;
    while (curr<index2) {
        if (nums[curr]==1) curr++;
        else if (nums[curr]==0) {
            index0++;
            if (index0 != curr) {
                nums[curr] = nums[index0];
                nums[index0]=0;
            }
            curr++;
        }
        else if (nums[curr]==2) {
            index2--;
            nums[curr] = nums[index2];
            nums[index2] = 2;
        }
    }
    return;

}

} // namespace sort
