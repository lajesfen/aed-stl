#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H

#include <iostream>
#define MAX_STACK_SIZE 100

template <typename T>
class Stack {
private:
    T list[MAX_STACK_SIZE];
    int top_index;

public:
    Stack() {
        top_index = -1;
    }

    int isFull() {
        if(top_index >= MAX_STACK_SIZE - 1) {
            return 1;
        }
        return 0;
    }

    int isEmpty() {
        if(top_index == -1) {
            return 1;
        }
        return 0;
    }

    T top() {
        return list[top_index];
    }

    void push(T e) {
        (top_index)++;
        list[top_index] = e;
    }

    T pop() {
        T item = top();
        (top_index)--;
        return item;
    }

    int size() {
        return top_index + 1;
    }
};

#endif //ALGORITHM_STACK_H
