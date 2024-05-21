#ifndef ALGORITHM_DOUBLY_LINKED_LIST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *next;
    Node *prev;

    Node() {
        next = nullptr;
        prev = nullptr;
    };
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T> *head;

public:
    DoublyLinkedList() {
        head = nullptr;
    };

    T front() {
        return head->data;
    };

    T back(){
        Node<T> *temp = head;

        while(temp->next != nullptr) {
            temp = temp->next;
        }

        return temp->data;
    };

    void pushFront(T data) {
        auto *temp = new Node<T>;
        temp->data = data;
        temp->next = head;
        temp->prev = nullptr;

        if (head != nullptr) {
            head->prev = temp;
        }

        head = temp;
    };

    void pushBack(T data) {
        auto *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;

        if(head == nullptr) {
            newNode->prev = nullptr;
            head = newNode;
            return;
        }

        Node<T> *temp = head;
        while(temp->next != nullptr) {
            temp = temp-> next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    };

    T popFront() {
        Node<T> *temp = head;
        head = head->next;

        if(head != nullptr) {
            head->prev = nullptr;
        }

        delete temp;
    }

    void popBack() {
        if(head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node<T> *temp = head;
            while(temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    T operator[](int i){
        Node<T> *temp = head;
        int t = 0;

        while(t != i) {
            temp = temp->next;
            ++t;
        }

        return temp->data;
    };

    bool empty(){
        return head == nullptr;
    };

    int size() {
        int size = 0;
        Node<T> *temp = head;

        while(temp != nullptr) {
            temp = temp->next;
            ++size;
        }

        return size;
    };

    void clear(){
        while(!empty()) {
            popFront();
        }
    };

    void sort() {
        Node<T> *temp = head;
        while (temp) {
            Node<T> *min = temp;
            Node<T> *r = temp->next;

            while (r) {
                if (min->data > r->data) {
                    min = r;
                }
                r = r->next;
            }

            T x = temp->data;
            temp->data = min->data;
            min->data = x;
            temp = temp->next;
        }
    };

    void reverse(){
        Node<T> *temp = head;
        Node<T> *prev = nullptr;

        while(temp != nullptr) {
            prev = temp->prev;
            temp->prev = temp->next;
            temp->next = prev;
            temp = temp->prev;
        }

        if(prev != nullptr) {
            head = prev->prev;
        }
    };

    void print() {
        Node<T> *temp = head;

        while(temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    };
};

#endif //ALGORITHM_DOUBLY_LINKED_LIST_H
