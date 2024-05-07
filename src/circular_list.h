#ifndef ALGORITHM_CIRCULAR_LIST_H
#define ALGORITHM_CIRCULAR_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *prev;
    Node *next;

    Node() = default;
    explicit Node(T data): data(data) {};
};

template <typename T>
class circular_linked_list {
private:
    Node<T> *head;

    circular_linked_list() {
        head = new Node<T>();
        head->next = head;
        head->prev = head;
    }

public:
    T front() {
        return head->data;
    }

    T back() {
        return head->prev->data;
    }

    void push_front(T data) {
        auto *node = new Node<T>(data);

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;

    }
};

#endif //ALGORITHM_CIRCULAR_LIST_H
