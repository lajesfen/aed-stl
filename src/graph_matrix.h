#ifndef ALGORITHM_GRAPH_MATRIX_H
#define ALGORITHM_GRAPH_MATRIX_H

#include <iostream>
#include <vector>

class GraphMatrix {
public:
    bool **adjMatrix;
    int size;

    GraphMatrix() {
        adjMatrix = nullptr;
        size = 0;
    }

    GraphMatrix(int _size) {
        size = _size;
        adjMatrix = new bool*[size];

        for(int i = 0; i < size; i++) {
            adjMatrix[i] = new bool[size];

            for(int j = 0; j < size; j++) {
                adjMatrix[i][j] = false;
            }
        }
    }

    ~GraphMatrix() {
        for (int i = 0; i < size; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }

    void addEdge(int i, int j, bool bidirectional) {
        adjMatrix[i][j] = true;
        if(bidirectional) adjMatrix[j][i] = true;
    }

    void removeEdge(int i, int j, bool bidirectional) {
        adjMatrix[i][j] = false;
        if(bidirectional) adjMatrix[j][i] = false;
    }

    bool hasEdge(int i, int j) {
        return adjMatrix[i][j];
    }

    std::vector<int> getNeighbors(int i) {
        std::vector<int> neighbors;
        for(int j = 0; j < size; j++) {
            if(adjMatrix[i][j]) {
                neighbors.push_back(j);
            }
        }
        return neighbors;
    }

    int getDegree(int i) {
        int degree = 0;
        for(int j = 0; j < size; j++) {
            if(adjMatrix[i][j]) {
                degree++;
            }
        }
        return degree;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << i << " : ";
            for (int j = 0; j < size; j++)
                std::cout << adjMatrix[i][j] << " ";
            std::cout << "\n";
        }
    }

};

#endif //ALGORITHM_GRAPH_MATRIX_H
