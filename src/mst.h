#ifndef ALGORITHM_MST_H
#define ALGORITHM_MST_H

#include <iostream>
#include <vector>
#include <src/min_heap.h>

typedef std::pair<int, int> pii;

class MST {
    void primMST(std::vector<std::vector<pii>> &graph, int V) {
        std::vector<int> key(V, INT_MAX);
        std::vector<int> parent(V, -1);
        std::vector<bool> inMST(V, false);

        MinHeap<pii> minHeap;
        minHeap.insert({0, 0});

        key[0] = 0;

        while (minHeap.root != nullptr) {
            MinHeap<pii>::Node *minNode = minHeap.pop();
            int u = minNode->data.second;
            delete minNode;

            inMST[u] = true;

            for (auto &[v, weight] : graph[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    minHeap.insert({key[v], v});
                }
            }
        }

        for (int i = 1; i < V; ++i) {
            std::cout << parent[i] << " - " << i << " : " << key[i] << std::endl;
        }
    }
};

#endif //ALGORITHM_MST_H
