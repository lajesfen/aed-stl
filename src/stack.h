#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H

#include <iostream>
#define MAX_STACK_SIZE 100

class stack {
private:
    struct element {
        int key;
    };

    element list[MAX_STACK_SIZE];
    int _top;

public:
    int isfull() {
        if(_top >= MAX_STACK_SIZE - 1) {
            return 1;
        }
        return 0;
    }

    int isempty() {
        if(_top == -1) {
            return 1;
        }
        return 0;
    }

    element top() {
        return list[_top];
    }

    void push(element e) {
        (_top)++;
        list[_top] = e;
    }

    void pop() {
        (_top)--;
    }
};

#endif //ALGORITHM_STACK_H
