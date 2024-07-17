#include <iostream>
#include <vector>
#include "src/queue.h"

class Solution {
private:
    std::vector<std::vector<int>> grid;
    int w;
    int h;

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

public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>> &inputGrid) {
        grid = inputGrid;
        h = grid.size();
        w = grid[0].size();

        if (grid[0][0] == 1 || grid[h-1][w-1] == 1) {
            return -1;
        }

        int ans = BFS(0, 0);
        return ans;
    }
};

int main() {
    Solution sol;
//    std::vector<std::vector<int>> grid {
//        {0, 0, 0},
//        {1, 1, 0},
//        {1, 1, 0}
//    };
    std::vector<std::vector<int>> grid {
            {0, 1},
            {1, 0},
    };

    std::cout << sol.shortestPathBinaryMatrix(grid);
    return 0;
}