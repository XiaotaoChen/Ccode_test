#include "CException.h"


// refer to: https://www.cnblogs.com/jiu0821/p/7207082.html


int main() {

    TRY
        int* s = NULL;
        *s = 1;
    END_TRY
    return 0;
}