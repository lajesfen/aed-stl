#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <iostream>

template <typename T>
struct AVLTree {
    struct Node {
        T data;
        Node *left;
        Node *right;
        int balanceFactor;

        Node() {
            left = nullptr;
            right = nullptr;
            balanceFactor = 0;
        }
    };

    Node *root;

    AVLTree() {
        root = NULL;
    };

    Node *insert(Node* node, int value) {
        if(node == nullptr) {
            node = new Node;
            node->data = value;

            if(root == nullptr) {
                root = node;
            }
            return node;
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return balance(node);
    }

    Node *remove(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return node;
        }

        return balance(node);
    }

    int height(Node *node) {
        if(node == nullptr) {
            return -1;
        }
        return 1 + std::max(height(node->left), height(node->right));
    };

    Node *rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateBalanceFactor(x);
        updateBalanceFactor(y);
        return y;
    }

    Node *rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateBalanceFactor(y);
        updateBalanceFactor(x);
        return x;
    }

    Node *rotateLeftThenRight(Node* n) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    Node *rotateRightThenLeft(Node* n) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    Node *balance(Node* node) {
        updateBalanceFactor(node);

        if (node->balanceFactor == -2) {
            if (node->left->balanceFactor <= 0) {
                return rotateRight(node);
            } else {
                return rotateLeftThenRight(node);
            }
        } else if (node->balanceFactor == 2) {
            if (node->right->balanceFactor >= 0) {
                return rotateLeft(node);
            } else {
                return rotateRightThenLeft(node);
            }
        }

        return node;
    };

    void updateBalanceFactor(Node* node) {
        node->balanceFactor = height(node->right) - height(node->left);
    }

    Node *getMinValue(Node *node) {
        if(node == nullptr) {
            return nullptr;
        } else if (node->left == nullptr) {
            return node;
        } else {
            return getMinValue(node->left);
        }
    }

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