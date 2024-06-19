#ifndef ALGORITHM_GRAPH_LIST_H
#define ALGORITHM_GRAPH_LIST_H

#include <iostream>
#include <vector>
#include <limits>

#include "src/queue.h"
#include "src/stack.h"
#include "src/min_heap.h"

const int INF = std::numeric_limits<int>::max();

template <typename T>
struct Node {
    T data;
    bool visited;
//    int index;
    std::vector<Node*> adjNodes;
    //std::vector<std::pair<Node<T>*, int>> adjNodes;

    Node() {
        visited = false;
    }
};

template <typename T>
class GraphList {
private:
    std::vector<Node<T>*> nodes;
//    int indexCounter;

public:
    GraphList() {
//        indexCounter = 0;
    }

    ~GraphList() {
        for (Node<T>* node : nodes) {
            delete node;
        }
    }

    void addNode(T value) {
        if(!getNode(value)) {
            Node<T> *newNode = new Node<T>();
            newNode->data = value;
//            newNode->index = indexCounter++;
            nodes.push_back(newNode);
        }
    }

    Node<T> *getNode(T value) {
        for (Node<T>* node : nodes) {
            if (node->data == value) {
                return node;
            }
        }
        return nullptr;
    }

    void addEdge(T node1, T node2) {
        Node<T> *fromNode = getNode(node1);
        Node<T> *toNode = getNode(node2);

        if (fromNode && toNode) {
            fromNode->adjNodes.push_back(toNode);
            //toNode->adjNodes.push_back(fromNode); // Uncomment if bidirectional
        }
    }

    void addEdge(T node1, T node2, int weight) {
        Node<T> *fromNode = getNode(node1);
        Node<T> *toNode = getNode(node2);

        if (fromNode && toNode) {
            fromNode->adjNodes.push_back({toNode, weight});
            //toNode->adjNodes.push_back(fromNode, weight); // Uncomment if bidirectional
        }
    }

    void BFS(T startValue) {
        Node<T>* startNode = getNode(startValue);
        if (!startNode) {
            return;
        }

        Queue<Node<T>*> q;
        q.enqueue(startNode);
        startNode->visited = true;

        while (!q.isEmpty()) {
            Node<T> *currentNode = q.front();
            q.dequeue();
            std::cout << currentNode->data << " ";

            for (Node<T>* adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    q.enqueue(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }
    }

    void DFS(T startValue) {
        Node<T>* startNode = getNode(startValue);
        if (!startNode) {
            return;
        }

        Stack<Node<T>*> s;
        s.push(startNode);
        startNode->visited = true;

        while (!s.isEmpty()) {
            Node<T> *currentNode = s.top();
            s.pop();
            std::cout << currentNode->data << " ";

            for (Node<T> *adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    s.push(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }
    }

    bool DFS(T startValue, T endValue) {
        Node<T>* startNode = getNode(startValue);
        Node<T>* endNode = getNode(endValue);

        Stack<Node<T>*> s;
        s.push(startNode);

        while (!s.isEmpty()) {
            Node<T> *currentNode = s.top();
            s.pop();

            if(currentNode == endNode) {
                return true;
            }

            for (Node<T> *adjNode : currentNode->adjNodes) {
                if (!adjNode->visited) {
                    s.push(adjNode);
                    adjNode->visited = true;
                }
            }
        }

        for (Node<T>* node : nodes) {
            node->visited = false;
        }

        return false;
    }
};

#endif //ALGORITHM_GRAPH_LIST_H
