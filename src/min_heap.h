#ifndef ALGORITHM_HEAP_H
#define ALGORITHM_HEAP_H

#include <iostream>
#include "src/queue.h"

template <typename T>
struct MinHeap {
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node() {
            left = nullptr;
            right = nullptr;
        }
    };

    Node *root;

    MinHeap() {
        root = NULL;
    };

    Node *insert(T value) {
        Node *node = new Node;
        node->data = value;

        if (root == nullptr) {
            root = node;
        } else {
            Queue<Node*> q;
            q.enqueue(root);

            while (!q.isEmpty()) {
                Node *temp = q.front();
                q.dequeue();

                if (temp->left == nullptr) {
                    temp->left = node;
                    heapifyUp(node);
                    break;
                } else if (temp->right == nullptr) {
                    temp->right = node;
                    heapifyUp(node);
                    break;
                } else {
                    q.enqueue(temp->left);
                    q.enqueue(temp->right);
                }
            }
        }

        return root;
    }

    Node *pop() {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else {
            Queue<Node*> q;
            q.enqueue(root);

            Node *node = nullptr;
            while (!q.isEmpty()) {
                node = q.front();
                q.dequeue();

                if (node->left != nullptr) {
                    q.enqueue(node->left);
                }
                if (node->right != nullptr) {
                    q.enqueue(node->right);
                }
            }

            Node *parentOfLastNode = getParent(root, node);
            std::swap(root->data, node->data);
            if (parentOfLastNode->left == node) {
                delete parentOfLastNode->left;
                parentOfLastNode->left = nullptr;
            } else {
                delete parentOfLastNode->right;
                parentOfLastNode->right = nullptr;
            }

            heapifyDown(root);
        }

        return root;
    }

    void heapifyUp(Node *node) {
        if(node == nullptr || node == root) {
            return;
        }

        Node *parent = nullptr;
        while (node != root) {
            parent = getParent(root, node);

            if(parent->data > node->data) {
                std::swap(parent->data, node->data);
            } else {
                break;
            }

            node = parent;
        }
    }

    void heapifyDown(Node *node) {
        if (node == nullptr) {
            return;
        }

        Node *maxNode = node;
        if (node->left != nullptr && node->left->data < maxNode->data) {
            maxNode = node->left;
        }
        if (node->right != nullptr && node->right->data < maxNode->data) {
            maxNode = node->right;
        }

        if (maxNode != node) {
            std::swap(node->data, maxNode->data);
            heapifyDown(maxNode);
        }
    }

    Node *getMinValue(Node *node) {
        Node *current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node *getParent(Node *root, Node *node) {
        if (root == nullptr || root == node) {
            return nullptr;
        }

        Queue<Node*> q;
        q.enqueue(root);

        while (!q.isEmpty()) {
            Node *temp = q.front();
            q.dequeue();

            if (temp->left == node || temp->right == node) {
                return temp;
            }

            if (temp->left != nullptr) {
                q.enqueue(temp->left);
            }
            if (temp->right != nullptr) {
                q.enqueue(temp->right);
            }
        }

        return nullptr;
    }

    void breadthFirstSearch() {
        Queue<Node*> q;
        q.enqueue(this->root);

        while(!q.isEmpty()) {
            Node *node = q.dequeue();
            std::cout << node->data << "\n";

            if(node->left != nullptr) {
                q.enqueue(node->left);
            }
            if(node->right != nullptr) {
                q.enqueue(node->right);
            }
        }
    }

    void inOrder(Node *node) {
        if(node == nullptr) {
            return;
        }

        inOrder(node->left);
        std::cout << node->data << "\n";
        inOrder(node->right);
    };
};

#endif //ALGORITHM_HEAP_H