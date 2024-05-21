#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#include <iostream>
#define MAX_SIZE 1000

struct Node {
    char key;
    int value;
    Node *next;

    Node() {
        next = nullptr;
    }
};

class HashTable {
private:
    Node **table;
    int size;

    static int hash(char key) {
        return key - 'a';
    }

public:
    explicit HashTable(int t) : size(t) {
        size = std::max(0, std::min(size, MAX_SIZE));
        table = new Node *[size]();
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            Node *current = table[i];
            while (current != nullptr) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(char key, int value) {
        int i = hash(key) % size;
        Node *newNode = new Node();
        newNode->key = key;
        newNode->value = value;

        if (table[i] == nullptr) {
            table[i] = newNode;
        } else {
            Node *current = table[i];
            while (current->next != nullptr) {
                if (current->key == key) {
                    current->value = value;
                    delete newNode;
                    return;
                }
                current = current->next;
            }
            if (current->key == key) {
                current->value = value;
                delete newNode;
            } else {
                current->next = newNode;
            }
        }
    }

    int get(char key) {
        int i = hash(key) % size;
        Node *current = table[i];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return 0;
    }

    void remove(char key) {
        int i = hash(key) % size;
        Node *current = table[i];
        Node *prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (prev == nullptr) {
            table[i] = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
    }

    void update(char key, int value) {
        int i = hash(key) % size;
        Node *current = table[i];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        insert(key, value);
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            Node *current = table[i];
            while (current != nullptr) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }
};

#endif //ALGORITHM_HASH_TABLE_H
