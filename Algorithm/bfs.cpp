#include <iostream>
#include <queue>
#include <vector>

std::vector<int> bfs(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<int> order;
    std::vector<bool> visited(adj.size());
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (int nbr : adj[node]) {
            if (!visited[nbr]) {
                visited[nbr] = true;
                q.push(nbr);
            }
        }
    }

    return order;
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},    // 0
        {0, 3, 4}, // 1
        {0, 4},    // 2
        {1, 4},    // 3
        {1, 2, 3}  // 4
    };

    int start = 0;
    std::vector<int> visitOrder = bfs(graph, start);

    std::cout << "BFS visit order starting from node " << start << ": ";
    for (int node : visitOrder) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}
