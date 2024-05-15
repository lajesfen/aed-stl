#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <iostream>

template <typename T>
struct AVLTree {
    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;
        int height;
    };

    NodeBT *root;

    AVLTree() {
        root = NULL;
    };

    NodeBT *insert(NodeBT *node, T value) {
        if(node == nullptr) {
            node = new NodeBT;
            node->data = value;
            node->height = 0;

            if(root == nullptr) {
                root = node;
            }
            return node;
        }

        if(value < node->data) {
            node->left = insert(node->left, value);
        } else if(value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
        balance(node);
        return node;
    };

    int height(NodeBT *node) {
        if(node == nullptr) {
            return 0;
        } else {
            return node->height;
        }
    };

    int getBalance(NodeBT *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    };

    NodeBT *rightRotate(NodeBT *y) {
        NodeBT *z = y->left;
        NodeBT *T2 = z->right;

        y->left = T2;
        z->right = y;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        z->height = std::max(height(z->left), height(z->right)) + 1;
        return z;
    };

    NodeBT *leftRotate(NodeBT *x) {
        NodeBT *z = x->right;
        NodeBT *T2 = z->left;

        x->right = T2;
        z->left = x;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        z->height = std::max(height(z->left), height(z->right)) + 1;
        return z;
    };

    NodeBT *balance(NodeBT *node) {
        if(getBalance(node) >= 2) {
            if(getBalance(node->left) <= -1) {
                return leftRotate(node);
            }
            return rightRotate(node);
        } else if (getBalance(node) <= -2) {
            if(getBalance(node->right) >= 1) {
                return rightRotate(node);
            }
            return leftRotate(node);
        }
    };

    void postOrder(NodeBT *node) {
        if(node == nullptr) {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << "\n";
    };

    void inOrder(NodeBT *node) {
        if(node == nullptr) {
            return;
        }

        inOrder(node->left);
        std::cout << node->data << " : " << node->height << "\n";
        inOrder(node->right);
    };

    void preOrder(NodeBT *node) {
        if(node == nullptr) {
            return;
        }

        std::cout << node->data << "\n";
        preOrder(node->left);
        preOrder(node->right);
    };
};

#endif //ALGORITHM_BINARY_TREE_H