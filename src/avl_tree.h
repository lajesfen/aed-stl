#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <iostream>

template <typename T>
struct AVLTree {
    struct Node {
        T data;
        Node *left;
        Node *right;
        int height;

        Node() {
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node *root;

    AVLTree() {
        root = NULL;
    };

    Node *insert(Node *node, T value) {
        if(node == nullptr) {
            node = new Node;
            node->data = value;

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
        return balance(node);
    }

    Node *remove(Node *node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = getMinValue(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
        return balance(node);
    }

    int height(Node *node) {
        if(node == nullptr) {
            return 0;
        } else {
            return node->height;
        }
    };

    int getBalance(Node *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    };

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    };

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    };

    Node *getMinValue(Node *node) {
        if(node == nullptr) {
            return nullptr;
        } else if (node->left == nullptr) {
            return node;
        } else {
            return getMinValue(node->left);
        }
    }

    Node *balance(Node *node) {
        int balanceFactor = getBalance(node);

        // Left-Left Case
        if(balanceFactor > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        // Right-Right Case
        if(balanceFactor < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        // Left-Right Case
        if(balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Left Case
        if(balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    };

    void postOrder(Node *node) {
        if(node == nullptr) {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << "\n";
    };

    void inOrder(Node *node) {
        if(node == nullptr) {
            return;
        }

        inOrder(node->left);
        std::cout << node->data << " : " << node->height << "\n";
        inOrder(node->right);
    };

    void preOrder(Node *node) {
        if(node == nullptr) {
            return;
        }

        std::cout << node->data << "\n";
        preOrder(node->left);
        preOrder(node->right);
    };
};

#endif //ALGORITHM_BINARY_TREE_H