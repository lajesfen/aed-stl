#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <iostream>
#include "src/queue.h"
#include "src/stack.h"

template <typename T>
struct BinaryTree {
    struct NodeBT {
        T data;
        NodeBT *left;
        NodeBT *right;
    };

    NodeBT *root;

    BinaryTree() {
        root = NULL;
    };

    //ToDO: Precesor y Predecesor

    bool find(NodeBT *node, T value) {
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

    NodeBT *insert(NodeBT *node, T value) {
        if(node == nullptr) {
            node = new NodeBT;
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

    NodeBT *getMinValue(NodeBT *node) {
        if(node == nullptr) {
            return;
        } else if (node->left == nullptr) {
            return node;
        } else {
            return getMinValue(node->left);
        }
    }

    NodeBT *getMaxValue(NodeBT *node) {
        if(node == nullptr) {
            return;
        } else if (node->right == nullptr) {
            return node;
        } else {
            return getMinValue(node->right);
        }
    }

    void remove(T value, NodeBT *node) {
        NodeBT *temp;
        if(node == nullptr) {
            return;
        } else if (value < node->data) {
            node->left = remove(value, node->left);
        } else if (value > node->data) {
            node->right = remove(value, node->left);
        } else if (node->left && node->right) {
            temp = getMinValue(node->right);
            node->data = temp->data;
            node->right = remove(node->data, node->right);
        } else {
            temp = node;
            if(node->left == nullptr) {
                node = node->right;
            } else if (node->right == nullptr) {
                node = node->left;
            }
            delete temp;
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
        std::cout << node->data << "\n";
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

    void breadthFirstSearch() {
        Queue<NodeBT*> q;
        q.enqueue(this->root);

        while(!q.isEmpty()) {
            NodeBT *node = q.dequeue();
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
        Stack<NodeBT*> stack;
        stack.push(this->root);

        while(!stack.isEmpty()) {
            NodeBT *node = stack.pop();
            std::cout << node->data << "\n";

            if(node->right != nullptr) {
                stack.push(node->right);
            }

            if(node->left != nullptr) {
                stack.push(node->left);
            }
        }
    }

    int depth(NodeBT *node) {
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
};

#endif //ALGORITHM_BINARY_TREE_H