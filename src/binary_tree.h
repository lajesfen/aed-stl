#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <iostream>
#include "src/queue.h"
#include "src/stack.h"

template <typename T>
struct BinaryTree {
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

    BinaryTree() {
        root = NULL;
    };

    bool find(Node *node, T value) {
        if(node == nullptr) {
            return false;
        } else if (value < node->data) {
            return find(node->left, value);
        } else if(value > node->data) {
            return find(node->right, value);
        } else {
            return true;
        }
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
        }

        return node;
    };

    Node *insertBT(Node *node, T value) {
        if(node == nullptr) {
            node = new Node;
            node->data = value;

            if(root == nullptr) {
                root = node;
            }
            return node;
        }

        Queue<Node*> q;
        q.enqueue(node);

        while(!q.isEmpty()) {
            Node *temp = q.front();
            q.dequeue();

            if(temp->left != nullptr) {
                q.enqueue(temp->left);
            } else {
                temp->left = new Node;
                temp->left->data = value;
                return node;
            }

            if(temp->right != nullptr) {
                q.enqueue(temp->right);
            } else {
                temp->right = new Node;
                temp->right->data = value;
                return node;
            }
        }
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

    Node *getMaxValue(Node *node) {
        if(node == nullptr) {
            return nullptr;
        } else if (node->right == nullptr) {
            return node;
        } else {
            return getMaxValue(node->right);
        }
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
        return node;
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
        std::cout << node->data << "\n";
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

    void depthFirstSearch() {
        Stack<Node*> stack;
        stack.push(this->root);

        while(!stack.isEmpty()) {
            Node *node = stack.pop();
            std::cout << node->data << "\n";

            if(node->right != nullptr) {
                stack.push(node->right);
            }

            if(node->left != nullptr) {
                stack.push(node->left);
            }
        }
    }

    int depth(Node *node) {
        if(node == nullptr) {
            return 0;
        } else {
            int left_depth = depth(node->left);
            int right_depth = depth(node->right);

            if(left_depth > right_depth) {
                return (left_depth + 1);
            } else {
                return (right_depth + 1);
            }
        }
    }

    Node *getPredecessor(Node *node) {
        if(node == nullptr || node->left == nullptr) {
            return nullptr;
        }
        return getMaxValue(node->left);
    }

    Node *getSuccessor(Node *node) {
        if(node == nullptr || node->right == nullptr) {
            return nullptr;
        }
        return getMinValue(node->left);
    }
};

#endif //ALGORITHM_BINARY_TREE_H
