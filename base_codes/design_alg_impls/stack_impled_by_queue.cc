#include <queue>

#include "../design_algs.h"

namespace design_alg {
    
    MyStack::MyStack() {}
    
    /** Push element x onto stack. */
    void MyStack::push(int x) {
        qu.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int MyStack::pop() {
        int n = qu.size();
        for (int i=0; i<n-1; i++) {
            qu.push(qu.front()); qu.pop();
        }
        int curr = qu.front(); qu.pop();
        return curr;
    }
    
    /** Get the top element. */
    int MyStack::top() {
        return qu.back();
    }
    
    /** Returns whether the stack is empty. */
    bool MyStack::empty() {
        return qu.empty();
    }
}