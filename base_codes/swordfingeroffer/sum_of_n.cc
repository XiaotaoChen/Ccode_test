#include "../swordfingeroffer.h"

namespace sword_finger_offer
{

class tmp {
public:
    tmp() { n++; sum += n; }
    static void reset() { n = 0; sum = 0; }
    static int getsum() { return sum; }
private:
    static int n;
    static int sum;
};

// 静态类成员变量必须在类外初始化．
int tmp::n = 0;
int tmp::sum = 0;

int solution1(int n) {
    tmp::reset();
    tmp* ptr = new tmp[n];
    
    delete[] ptr;
    ptr = nullptr;

    return tmp::getsum();
}


// 方法2 虚函数保证基类指针调用子类方法
// 注意　arr只能是基类指针，而不能为基类对象

class A;
A* arr[2];

class A {
public:
    virtual int sum(int n) { return 0;}
};

class B: public A {
public:
    virtual int sum(int n) { return arr[!!n]->sum(n-1) + n;};
};

int solution2(int n) {
    A a;
    B b;
    arr[0] = &a;
    arr[1] = &b;
    return arr[1]->sum(n);
}


// 方法3 函数指针

typedef int(*func)(int n);

int f1(int n) {
    return 0;
}

int f2(int n) {
    static func fs[2] = {f1, f2};
    return fs[!!n](n-1) + n;
}

// 方法4 利用sizeof
int solution4(int n) {
    bool arr[n][n+1];
    return sizeof(arr)>>1;
}

int nsum(int n) {

    // int result = solution1(n);
    // int result = solution2(n);
    // int result = f2(n);
    int result = solution4(n);

    return result;
}

} // namespace sword_finger_offer
