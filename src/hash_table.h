#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#include <iostream>
#define MAX_SIZE 1000

struct Node {
    char key;
    int value;
    Node *next;

    Node(char k, int v) {
        value = v;
        key = k;
        next = nullptr;
    }
};

class HashTable {
private:
    Node **table;
    int size;

    static int hash(char key) { // Modify depending on Hashing method
        return key - 'a';
    }

public:
    HashTable(int t) : size(t) {
        size = std::max(0, std::min(size, MAX_SIZE));
        table = new Node *[size]();
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i)
        {
            Node *current = table[i];
            while (current != nullptr)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(char key, int value) {
        int i = hash(key) % size;
        Node *new_node = new Node(key, value);

        if (table[i] == nullptr)
            table[i] = new_node;
        else {
            Node *current = table[i];
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
                current->next = new_node;
            }
        }
    }

    int find(char key) {
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
};

#endif //ALGORITHM_HASH_TABLE_H
