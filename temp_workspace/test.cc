#include <cstdio>
#include <string>

struct point
{
    int x, y;
    point():x(0), y(0){}
    point(int a, int b):x(a), y(b){}
    void print() {
        printf("point:(%d, %d)\n", x, y);
    }
};


int main() {
    point p1 = point(1,2);
    p1.print();


    return 0;
}
