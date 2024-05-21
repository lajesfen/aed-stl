#ifndef ALGORITHM_FORWARD_LIST_H
#define ALGORITHM_FORWARD_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *next;

    Node() {
        next = nullptr;
    };
};

template <typename T>
class ForwardList {
private:
    Node<T> *head;

public:
    ForwardList() {
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
        head = temp;
    };

    void pushBack(T data) {
        auto *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;

        if(head == nullptr) {
            head = newNode;
            return;
        }

        Node<T> *temp = head;
        while(temp->next != nullptr) {
            temp = temp-> next;
        }

        temp->next = newNode;
        newNode->next = nullptr;
    };

    T popFront() {
        Node<T> *temp = head;
        head = head->next;
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
        Node<T> *next = nullptr;

        while(temp != nullptr) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
    };

    void print() {
        Node<T> *temp = head;

        while(temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    };
};

#endif //ALGORITHM_FORWARD_LIST_H
