#include <cstring>
#include <cstdio>
#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

bool increment(char* member) {
    int len = strlen(member);
    for (int i=len-1; i>=0; i--) {
        int num = member[i] - '0';
        if (i == len-1) num++;
        if (num <10) {
            member[i] = '0' + num;
            return true;
        }
        else {
            if (i==0) return false;
            else {
                member[i] = '0';
                member[i-1] += 1;
            }
        }
    }
    return true;
}

bool PrintNumber(char* member) {
    int len = strlen(member);
    bool isbegin0 = true;
    for (int i=0; i<len; i++) {
        if (isbegin0 && member[i]!='0') isbegin0 = false;
        if (!isbegin0) printf("%c", member[i]);
    }
    printf("\n");
}

void print1ToMaxNDigits(int n) {
    if (n == 0) return;
    char* member = new char[n+1];
    memset(member, '0', n);
    member[n] = '\0';
    while(increment(member)) {
        PrintNumber(member);
    }

    delete[] member;
}

void print1ToMaxNDigits_v2(int n) {
    if (n == 0) return ;
    char* member = new char[n+1];
    memset(member, '0', n);
    member[n] = '\0';
    print_dfs(member, 0, n);
    delete[] member;
}


void print_dfs(char* member, int depth, int n) {
    if (depth == n)  {
        PrintNumber(member);
        return;
    }
    for (int i=0; i<10; i++) {
        member[depth] = '0' + i;
        print_dfs(member, depth+1, n);
    }
}

} // namespace sword_finger_offer
