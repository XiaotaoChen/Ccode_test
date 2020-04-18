#ifndef SWORD_FINGER_OFFER_
#define SWORD_FINGER_OFFER_

namespace sword_finger_offer
{

// interview 17 打印１到ｎ位最大数的所有可能
void print1ToMaxNDigits(int n);

bool increment(char* member);

bool PrintNumber(char* member);

void print1ToMaxNDigits_v2(int n);
void print_dfs(char* member, int depth, int n);

} // namespace sword_finger_offer


#endif