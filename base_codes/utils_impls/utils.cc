#include<cstdio>

#include "../utils.h"

int utils::compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}