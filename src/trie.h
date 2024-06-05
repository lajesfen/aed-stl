#ifndef ALGORITHM_TRIE_H
#define ALGORITHM_TRIE_H

#include <iostream>

struct TrieNode {
    TrieNode *childNode[26];
    bool wordEnd;

    TrieNode() {
        wordEnd = false;
        for(auto & i : childNode) {
            i = nullptr;
        }
    }
};

struct Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(std::string &key) {
        TrieNode *temp = root;

        for(auto c: key) {
            if(temp->childNode[c - 'a'] == nullptr) {
                TrieNode *node = new TrieNode();
                temp->childNode[c - 'a'] = node;
            }

            temp = temp->childNode[c - 'a'];
        }

        temp->wordEnd = true;
    }

    bool search(const std::string &key) {
        TrieNode *temp = root;

        for(auto c : key) {
            if(temp->childNode[c - 'a'] == nullptr) {
                return false;
            }

            temp = temp->childNode[c - 'a'];
        }

        return (temp->wordEnd == true);
    }
};

#endif //ALGORITHM_TRIE_H
