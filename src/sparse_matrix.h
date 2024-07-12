#ifndef ALGORITHM_SPARSE_MATRIX_H
#define ALGORITHM_SPARSE_MATRIX_H

#include <iostream>
#include <vector>

class Node {
public:
    int data;
    int posRow;
    int posCol;
    Node *nextRow;
    Node *nextCol;

    Node(int row, int col, int value) : data(value), posRow(row), posCol(col), nextRow(nullptr), nextCol(nullptr) {}
};

class SparseMatrix {
private:
    std::vector<Node*> rows;
    std::vector<Node*> cols;
    int nCols;
    int nRows;

public:
    SparseMatrix(int nRows, int nCols) : nRows(nRows), nCols(nCols) {
        rows.resize(nRows, nullptr);
        cols.resize(nCols, nullptr);
    }

    Node *insertRow(Node *head, Node *newNode) {
        if (!head || newNode->posCol < head->posCol) {
            newNode->nextRow = head;
            return newNode;
        }

        Node* curr = head;
        while (curr->nextRow && curr->nextRow->posCol < newNode->posCol) {
            curr = curr->nextRow;
        }

        newNode->nextRow = curr->nextRow;
        curr->nextRow = newNode;
        return head;
    }

    Node *insertCol(Node *head, Node *newNode) {
        if (!head || newNode->posRow < head->posRow) {
            newNode->nextCol = head;
            return newNode;
        }

        Node* curr = head;
        while (curr->nextCol && curr->nextCol->posRow < newNode->posRow) {
            curr = curr->nextCol;
        }

        newNode->nextCol = curr->nextCol;
        curr->nextCol = newNode;
        return head;
    }

    void insert(int row, int col, int value) {
        if (row >= nRows || col >= nCols || row < 0 || col < 0) {
            return;
        }

        Node *newNode = new Node(row, col, value);

        rows[row] = insertRow(rows[row], newNode);
        cols[col] = insertCol(cols[col], newNode);
    }

    void print() {
        for (int i = 0; i < nRows; ++i) {
            Node* curr = rows[i];
            while (curr) {
                std::cout << "Row: " << curr->posRow << " Col: " << curr->posCol << " Value: " << curr->data << "\n";
                curr = curr->nextRow;
            }
        }
    }
};

#endif //ALGORITHM_SPARSE_MATRIX_H
