#ifndef ALGORITHM_CIRCULAR_LIST_H
#define ALGORITHM_CIRCULAR_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *prev;
    Node *next;

    explicit Node(T data) {
        this->data = data;
        prev = nullptr;
        next = nullptr;
    };
};

template <typename T>
class CircularLinkedList {
private:
    Node<T> *head;

public:
    CircularLinkedList() {
        head = new Node<T>();
        head->next = head;
        head->prev = head;
    }

    ~CircularLinkedList() {
        while (!isEmpty()) {
            popFront();
        }

        delete head;
    }

    bool isEmpty() {
        return head == head->next;
    }

    T front() {
        return head->next->data;
    }

    T back() {
        return head->prev->data;
    }

    void pushFront(T data) {
        auto *node = new Node<T>(data);

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void popFront() {
        Node<T> *temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
    }
};

#endif //ALGORITHM_CIRCULAR_LIST_H
