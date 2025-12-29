#include <iostream>
#include <vector>

void dfs(const std::vector<std::vector<int>>& adj, int node, std::vector<bool>& visited,
         std::vector<int>& order) {
    visited[node] = true;
    order.push_back(node);

    for (int nbr : adj[node]) {
        if (!visited[nbr]) {
            dfs(adj, nbr, visited, order);
        }
    }
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
    std::vector<bool> visited(graph.size());
    std::vector<int> visitOrder;

    dfs(graph, start, visited, visitOrder);

    std::cout << "DFS visit order starting from node " << start << ": ";
    for (int node : visitOrder) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}
