#ifndef ALGORITHM_B_TREE_H
#define ALGORITHM_B_TREE_H

#include <iostream>

#define MAX_KEYS 3
#define MIN_KEYS 1
#define MAX_CHILDREN 4

struct BTree {
    struct Node {
        int n;
        int key[MAX_KEYS];
        Node *children[MAX_CHILDREN];
        bool leaf;

        Node(bool isLeaf) {
            n = 0;
            leaf = isLeaf;

            for(auto & i : children) {
                i = nullptr;
            }
        }
    };

    Node *root;

    BTree() {
        root = nullptr;
    }

    void traverse(Node *node) {
        int i;
        for (i = 0; i < node->n; i++) {
            if (!node->leaf)
                traverse(node->children[i]);
            std::cout << " " << node->key[i];
        }
        if (!node->leaf)
            traverse(node->children[i]);
    }

    Node* search(Node *node, int k) {
        int i = 0;
        while (i < node->n && k > node->key[i])
            i++;
        if (node->key[i] == k)
            return node;
        if (node->leaf)
            return nullptr;
        return search(node->children[i], k);
    }

    void insert(int k) {
        if (root == nullptr) {
            root = new Node(true);
            root->key[0] = k;
            root->n = 1;
        } else {
            if (root->n == MAX_KEYS) {
                Node *s = new Node(false);
                s->children[0] = root;
                splitChild(s, 0, root);
                int i = 0;
                if (s->key[0] < k)
                    i++;
                insertNonFull(s->children[i], k);
                root = s;
            } else {
                insertNonFull(root, k);
            }
        }
    }

    void insertNonFull(Node *node, int k) {
        int i = node->n - 1;
        if (node->leaf) {
            while (i >= 0 && node->key[i] > k) {
                node->key[i + 1] = node->key[i];
                i--;
            }
            node->key[i + 1] = k;
            node->n++;
        } else {
            while (i >= 0 && node->key[i] > k)
                i--;
            if (node->children[i + 1]->n == MAX_KEYS) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (node->key[i + 1] < k)
                    i++;
            }
            insertNonFull(node->children[i + 1], k);
        }
    }

    void splitChild(Node *parent, int i, Node *fullChild) {
        Node *newChild = new Node(fullChild->leaf);
        newChild->n = MAX_KEYS / 2;
        for (int j = 0; j < MAX_KEYS / 2; j++)
            newChild->key[j] = fullChild->key[j + MAX_KEYS / 2 + 1];
        if (!fullChild->leaf) {
            for (int j = 0; j <= MAX_KEYS / 2; j++)
                newChild->children[j] = fullChild->children[j + MAX_KEYS / 2 + 1];
        }
        fullChild->n = MAX_KEYS / 2;
        for (int j = parent->n; j >= i + 1; j--)
            parent->children[j + 1] = parent->children[j];
        parent->children[i + 1] = newChild;
        for (int j = parent->n - 1; j >= i; j--)
            parent->key[j + 1] = parent->key[j];
        parent->key[i] = fullChild->key[MAX_KEYS / 2];
        parent->n++;
    }

    void remove(int k) {
        if (!root) {
            std::cout << "The tree is empty\n";
            return;
        }
        remove(root, k);
        if (root->n == 0) {
            Node *temp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->children[0];
            delete temp;
        }
    }

    void remove(Node *node, int k) {
        int idx = findKey(node, k);
        if (idx < node->n && node->key[idx] == k) {
            if (node->leaf)
                removeFromLeaf(node, idx);
            else
                removeFromNonLeaf(node, idx);
        } else {
            if (node->leaf) {
                std::cout << "The key " << k << " is not in the tree\n";
                return;
            }
            bool flag = ((idx == node->n) ? true : false);
            if (node->children[idx]->n < MIN_KEYS + 1)
                fill(node, idx);
            if (flag && idx > node->n)
                remove(node->children[idx - 1], k);
            else
                remove(node->children[idx], k);
        }
    }

    int findKey(Node *node, int k) {
        int idx = 0;
        while (idx < node->n && node->key[idx] < k)
            ++idx;
        return idx;
    }

    void removeFromLeaf(Node *node, int idx) {
        for (int i = idx + 1; i < node->n; ++i)
            node->key[i - 1] = node->key[i];
        node->n--;
    }

    void removeFromNonLeaf(Node *node, int idx) {
        int k = node->key[idx];
        if (node->children[idx]->n >= MIN_KEYS + 1) {
            int pred = getPred(node, idx);
            node->key[idx] = pred;
            remove(node->children[idx], pred);
        } else if (node->children[idx + 1]->n >= MIN_KEYS + 1) {
            int succ = getSucc(node, idx);
            node->key[idx] = succ;
            remove(node->children[idx + 1], succ);
        } else {
            merge(node, idx);
            remove(node->children[idx], k);
        }
    }

    int getPred(Node *node, int idx) {
        Node *cur = node->children[idx];
        while (!cur->leaf)
            cur = cur->children[cur->n];
        return cur->key[cur->n - 1];
    }

    int getSucc(Node *node, int idx) {
        Node *cur = node->children[idx + 1];
        while (!cur->leaf)
            cur = cur->children[0];
        return cur->key[0];
    }

    void fill(Node *node, int idx) {
        if (idx != 0 && node->children[idx - 1]->n >= MIN_KEYS + 1)
            borrowFromPrev(node, idx);
        else if (idx != node->n && node->children[idx + 1]->n >= MIN_KEYS + 1)
            borrowFromNext(node, idx);
        else {
            if (idx != node->n)
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    void borrowFromPrev(Node *node, int idx) {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx - 1];
        for (int i = child->n - 1; i >= 0; --i)
            child->key[i + 1] = child->key[i];
        if (!child->leaf) {
            for (int i = child->n; i >= 0; --i)
                child->children[i + 1] = child->children[i];
        }
        child->key[0] = node->key[idx - 1];
        if (!child->leaf)
            child->children[0] = sibling->children[sibling->n];
        node->key[idx - 1] = sibling->key[sibling->n - 1];
        child->n++;
        sibling->n--;
    }

    void borrowFromNext(Node *node, int idx) {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx + 1];
        child->key[child->n] = node->key[idx];
        if (!child->leaf)
            child->children[child->n + 1] = sibling->children[0];
        node->key[idx] = sibling->key[0];
        for (int i = 1; i < sibling->n; ++i)
            sibling->key[i - 1] = sibling->key[i];
        if (!sibling-> leaf) {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->children[i - 1] = sibling->children[i];
        }
        child->n++;
        sibling->n--;
    }

    void merge(Node *node, int idx) {
        Node *child = node->children[idx];
        Node *sibling = node->children[idx + 1];
        child->key[MIN_KEYS] = node->key[idx];
        for (int i = 0; i < sibling->n; ++i)
            child->key[i + MIN_KEYS + 1] = sibling->key[i];
        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; ++i)
                child->children[i + MIN_KEYS + 1] = sibling->children[i];
        }
        for (int i = idx + 1; i < node->n; ++i)
            node->key[i - 1] = node->key[i];
        for (int i = idx + 2; i <= node->n; ++i)
            node->children[i - 1] = node->children[i];
        child->n += sibling->n + 1;
        node->n--;
        delete sibling;
    }

};

#endif //ALGORITHM_B_TREE_H
