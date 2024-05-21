#ifndef ALGORITHM_CIRCULAR_LIST_H
#define ALGORITHM_CIRCULAR_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *prev;
    Node *next;

    Node() {
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

    bool isEmpty() {
        return head->next == head;
    }

    T front() {
        return head->next->data;
    }

    T back() {
        return head->prev->data;
    }

    void pushFront(T data) {
        auto *node = new Node<T>;
        node->data = data;

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void pushBack(T data) {
        auto *node = new Node<T>;
        node->data = data;

        node->next = head;
        node->prev = head->prev;

        head->prev->next = node;
        head->prev = node;
    }

    void popFront() {
        Node<T> *temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
    }

    void popBack() {
        Node<T> *temp = head->prev;
        head->prev = temp->prev;
        temp->prev->next = head;
        delete temp;
    }

    void print() {
        Node<T> *temp = head->next;
        while (temp != head) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif //ALGORITHM_CIRCULAR_LIST_H
