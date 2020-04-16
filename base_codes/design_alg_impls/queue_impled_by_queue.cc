#include "../design_algs.h"

namespace design_alg
{

MyQueue::MyQueue(){}

void MyQueue::push(int x) {
    s1.push(x);
}

int MyQueue::pop() {
    if (s2.empty()) {
        while(!s1.empty()) {
            s2.push(s1.top()); s1.pop();
        }
    }
    if (s2.empty()) return -1;
    int front = s2.top(); s2.pop();
    return front;
}

int MyQueue::front() {
    if (s2.empty()) {
        while(!s1.empty()) {
            s2.push(s1.top()); s1.pop();
        }
    }
    return s2.top();
}

bool MyQueue::empty() {
    return s1.empty() && s2.empty();
}

} // namespace design_alg
