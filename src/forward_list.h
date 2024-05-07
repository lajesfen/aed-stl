#ifndef ALGORITHM_FORWARD_LIST_H
#define ALGORITHM_FORWARD_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *next;

    Node() {
        data = NULL;
        next = nullptr;
    };
};

template <typename T>
class ForwardList {
private:
    Node<T> *head;

public:
    ForwardList() {
        head = NULL;
    };

    T front() {
        return head->data;
    };

    T back(){
        Node<T> *temp = head;

        while(temp->next != NULL) {
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
        auto *temp = new Node<T>;
        temp->data = data;

        Node<T> *temp2 = head;

        while(temp2->next != NULL) {
            temp2 = temp2-> next;
        }

        temp2->next = temp;
        temp->next = NULL;
    };

    T popFront() {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T popBack() {
        if(head->next == NULL) {
            delete head;
            head = NULL;
        } else {
            Node<T> *temp = head;
            while(temp->next->next != NULL) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
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
        return head == NULL;
    };

    int size() {
        int size = 0;
        Node<T> *temp = head;

        while(temp != NULL) {
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
        Node<T> *prev = NULL;
        Node<T> *next = NULL;

        while(temp != NULL) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
    };

    void print() {
        Node<T> *temp = head;

        while(temp->next != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    };
};

#endif //ALGORITHM_FORWARD_LIST_H
