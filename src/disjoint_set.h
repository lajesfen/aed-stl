#ifndef ALGORITHM_DISJOINT_SET_H
#define ALGORITHM_DISJOINT_SET_H

#include <vector>
#include <algorithm>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

    struct Edge {
        int u, v, weight;
        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    };

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size);

        for (int i = 0; i < size; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }

    void kruskalMST(std::vector<Edge> &edges, int V) {
        std::sort(edges.begin(), edges.end());
        DisjointSet ds(V);

        std::vector<Edge> result;

        for (const auto &edge : edges) {
            int u = edge.u;
            int v = edge.v;
            if (ds.find(u) != ds.find(v)) {
                result.push_back(edge);
                ds.unite(u, v);
            }
        }
    }


};

#endif //ALGORITHM_DISJOINT_SET_H
