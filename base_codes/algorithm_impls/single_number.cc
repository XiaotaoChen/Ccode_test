
int singleNumber(int A[], int n) {
    int a = 0;
    for (int i=0; i< n; i++) {
        a = a^A[i];
    }
    return a;
}

int singleNumber_v2(int A[], int n) {
    int one = 0;
    int two = 0;
    int three = 0;
    for (int i=0; i<n; i++) {
        two |= one & A[i]; // there is no case: one=1, A=1, two=1, one/two at most one to 1.
        one = one ^ A[i];
        three = one & two;
        one &= ~three;
        two &= ~three;
    }
    return one;
}

int singleNumber_v3(int A[], int n) {
    int result=0;
    for (int i=0; i<32; i++) {
        int bits = 0;
        for(int j=0; j<n; j++) {
            bits += (A[j]>>i) & 1;
        }
        result |= ((bits%3)<<i);
    }
    return result;
}