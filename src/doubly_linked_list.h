#ifndef ALGORITHM_DOUBLY_LINKED_LIST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_H

#include <iostream>

// ToDo
// ToDo
// ToDo

template <typename T>
struct node {
    T data;
    node *next;

    node() {};
};

template <typename T>
class forward_list {
private:
    node<T> *head;

public:
    forward_list() {
        head = NULL;
    };

    T front() {
        return head->data;
    };

    T back(){
        node<T> *temp = head;

        while(temp->next != NULL) {
            temp = temp->next;
        }

        return temp->data;
    };

    void push_front(T data) {
        auto *temp = new node<T>;
        temp->data = data;
        temp->next = head;
        head = temp;
    };

    void push_back(T data) {
        auto *temp = new node<T>;
        temp->data = data;

        node<T> *temp2 = head;

        while(temp2->next != NULL) {
            temp2 = temp2-> next;
        }

        temp2->next = temp;
        temp->next = NULL;
    };

    T pop_front() {
        node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    T pop_back() {
        if(head->next == NULL) {
            delete head;
            head = NULL;
        } else {
            node<T> *temp = head;
            while(temp->next->next != NULL) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
        }
    }

    T operator[](int i){
        node<T> *temp = head;
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
        node<T> *temp = head;

        while(temp != NULL) {
            temp = temp->next;
            ++size;
        }

        return size;
    };

    void clear(){
        while(!empty()) {
            pop_front();
        }
    };

    void sort() {
        node<T> *temp = head;
        while (temp) {
            node<T> *min = temp;
            node<T> *r = temp->next;

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
        node<T> *temp = head;
        node<T> *prev = NULL;
        node<T> *next = NULL;

        while(temp != NULL) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
    };

    void print() {
        node<T> *temp = head;

        while(temp->next != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    };
};

#endif //ALGORITHM_DOUBLY_LINKED_LIST_H
