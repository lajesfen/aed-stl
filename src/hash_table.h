#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#include <iostream>
#define MAX_SIZE 1000

struct node {
    char key;
    int value;
    node *next;

    node(char k, int v) : value(v), key(k), next(nullptr) {}
};

class hash_table {
private:
    node **table;
    int size;

    static int hash(char key) { // Modify depending on Hashing method
        return key - 'a';
    }

public:
    hash_table(int t) : size(t) {
        size = std::max(0, std::min(size, MAX_SIZE));
        table = new node *[size]();
    }

    ~hash_table() {
        for (int i = 0; i < size; ++i)
        {
            node *current = table[i];
            while (current != nullptr)
            {
                node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(char key, int value) {
        int i = hash(key) % size;
        node *newNode = new node(key, value);

        if (table[i] == nullptr)
            table[i] = newNode;
        else {
            node *current = table[i];
            while (current->next != nullptr) {
                if (current->key == key) {
                    current->value = value;
                    return;
                }
                current = current->next;
            }
            if (current->key == key) {
                current->value = value;
            } else {
                current->next = newNode;
            }
        }
    }

    int hashing(char key) {
        int i = hash(key) % size;
        node *current = table[i];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return 0;
    }
};

#endif //ALGORITHM_HASH_TABLE_H
