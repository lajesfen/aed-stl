#ifndef ALGORITHM_LOOSE_CODE_H
#define ALGORITHM_LOOSE_CODE_H

#include <vector>
#include <iostream>
using namespace std;

/// COMPONENTES FUERTEMENTE CONEXOS
class GFG {
public:
    // dfs Function to reach destination
    bool dfs(int curr, int des, vector<vector<int> >& adj,
             vector<int>& vis)
    {

        // If curr node is destination return true
        if (curr == des) {
            return true;
        }
        vis[curr] = 1;
        for (auto x : adj[curr]) {
            if (!vis[x]) {
                if (dfs(x, des, adj, vis)) {
                    return true;
                }
            }
        }
        return false;
    }

    // To tell whether there is path from source to
    // destination
    bool isPath(int src, int des, vector<vector<int> >& adj)
    {
        vector<int> vis(adj.size() + 1, 0);
        return dfs(src, des, adj, vis);
    }

    // Function to return all the strongly connected
    // component of a graph.
    vector<vector<int> > findSCC(int n,
                                 vector<vector<int> >& a)
    {
        // Stores all the strongly connected components.
        vector<vector<int> > ans;

        // Stores whether a vertex is a part of any Strongly
        // Connected Component
        vector<int> is_scc(n + 1, 0);

        vector<vector<int> > adj(n + 1);

        for (int i = 0; i < a.size(); i++) {
            adj[a[i][0]].push_back(a[i][1]);
        }

        // Traversing all the vertices
        for (int i = 1; i <= n; i++) {

            if (!is_scc[i]) {

                // If a vertex i is not a part of any SCC
                // insert it into a new SCC list and check
                // for other vertices whether they can be
                // thr part of thidl ist.
                vector<int> scc;
                scc.push_back(i);

                for (int j = i + 1; j <= n; j++) {

                    // If there is a path from vertex i to
                    // vertex j and vice versa put vertex j
                    // into the current SCC list.
                    if (!is_scc[j] && isPath(i, j, adj)
                        && isPath(j, i, adj)) {
                        is_scc[j] = 1;
                        scc.push_back(j);
                    }
                }

                // Insert the SCC containing vertex i into
                // the final list.
                ans.push_back(scc);
            }
        }
        return ans;
    }
};

/// DIJKSTRA
#define V 9
int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the
    // shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is
    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

/// TOPOLOGICAL SORT
void topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
void topologicalSort()
{
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}





/**
 * Loose Problems
 **/

// 1. Find isles (1) in grid.
bool DFS(int currRow, int currCol, std::vector<std::vector<int>> &vis) {
    if (currRow < 0 || currRow >= h || currCol < 0 || currCol >= w || vis[currRow][currCol] || grid[currRow][currCol] == '0') {
        return false;
    }

    vis[currRow][currCol] = 1;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto dir: directions) {
        DFS(currRow + dir.first, currCol + dir.second, vis);
    }
    return true;
}

std::vector<std::vector<int>> findSCC() {
    std::vector<std::vector<int>> ans;
    std::vector<std::vector<int>> vis(h, std::vector<int>(w, 0));

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(!vis[i][j] && grid[i][j] == '1') {
                std::vector<int> scc;

                if(DFS(i, j, vis)) {
                    scc.push_back(i * w + j);
                    ans.push_back(scc);
                }
            }
        }
    }

    return ans;
}

// 2. Find isles (1) in grid (USING BFS)
bool BFS(int currRow, int currCol, std::vector<std::vector<int>> &vis) {
    Queue<std::pair<int, int>> q;
    q.enqueue({currRow, currCol});
    vis[currRow][currCol] = 1;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.isEmpty()) {
        auto [row, col] = q.front();
        q.dequeue();

        // Explore adjacent cells
        for (auto dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            // Check if the new cell is valid and not visited
            if (newRow >= 0 && newRow < h && newCol >= 0 && newCol < w && grid[newRow][newCol] == '1' && !vis[newRow][newCol]) {
                q.enqueue({newRow, newCol});
                vis[newRow][newCol] = 1;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> findSCC(std::vector<std::vector<char>> &grid) {
    int h = grid.size();
    int w = grid[0].size();
    std::vector<std::vector<int>> ans;
    std::vector<std::vector<int>> vis(h, std::vector<int>(w, 0));

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (!vis[i][j] && grid[i][j] == '1') {
                std::vector<int> scc;

                if (BFS(i, j, vis, grid)) {
                    scc.push_back(i * w + j);
                    ans.push_back(scc);
                }
            }
        }
    }

    return ans;
}

// 3. Find if there's a path from top-left to bottom-right
int BFS(int currRow, int currCol) {
    Queue<std::pair<int, int>> q;
    q.enqueue({currRow, currCol});
    grid[currRow][currCol] = 1;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    while (!q.isEmpty()) {
        auto [row, col] = q.front();
        q.dequeue();

        // Explore adjacent cells
        for (auto dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            // Check if the new cell is valid and not visited
            if (newRow >= 0 && newRow < h && newCol >= 0 && newCol < w && grid[newRow][newCol] == 0 && !grid[newRow][newCol]) {
                if (newRow == h-1 && newCol == w-1) {
                    return grid[row][col] + 1;
                }

                q.enqueue({newRow, newCol});
                grid[newRow][newCol] = grid[row][col] + 1;
            }
        }
    }
    return -1;
}


#endif //ALGORITHM_LOOSE_CODE_H
