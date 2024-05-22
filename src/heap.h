#ifndef ALGORITHM_HEAP_H
#define ALGORITHM_HEAP_H

#include <iostream>
#include "src/queue.h"

template <typename T>
struct MaxHeap {
    std::vector<T> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void heapifyUp(int i) {
        if (i && heap[parent(i)] < heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }

    void heapifyDown(int i) {
        int l = left(i);
        int r = right(i);

        int largest = i;
        if (l < heap.size() && heap[l] > heap[i])
            largest = l;
        if (r < heap.size() && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    void insert(int key) {
        heap.push_back(key);
        int i = heap.size() - 1;
        heapifyUp(i);
    }

    void remove() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();

        heapifyDown(0);
    }

    int getMax() { return heap[0]; }

    void print() {
        for (int i = 0; i < heap.size(); ++i)
            std::cout << heap[i] << " ";
        std::cout << "\n";
    }
};

#endif //ALGORITHM_HEAP_H