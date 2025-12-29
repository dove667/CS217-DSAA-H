#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
public:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
    }

    void topologicalSortKahn() {
        std::vector<int> inDegree(vertices, 0);

        for (int i = 0; i < vertices; ++i) {
            for (int neighbor : adjacencyList[i]) {
                inDegree[neighbor]++;
            }
        }

        std::queue<int> q;
        for (int i = 0; i < vertices; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> result;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);

            for (int neighbor : adjacencyList[u]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        std::cout << "Topological order (Kahn's Algorithm): ";
        for (int node : result) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    void topologicalSortDFS() {
        std::vector<bool> visited(vertices, false);
        std::stack<int> st;

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i]) {
                topologicalSortDFSUtil(i, visited, st);
            }
        }

        std::cout << "Topological order (DFS): ";
        while (!st.empty()) {
            std::cout << st.top() << " ";
            st.pop();
        }
        std::cout << std::endl;
    }

private:
    void topologicalSortDFSUtil(int u, std::vector<bool>& visited, std::stack<int>& st) {
        visited[u] = true;

        for (int neighbor : adjacencyList[u]) {
            if (!visited[neighbor]) {
                topologicalSortDFSUtil(neighbor, visited, st);
            }
        }

        st.push(u);
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    std::cout << "Graph edges: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1" << std::endl;
    g.topologicalSortKahn();
    g.topologicalSortDFS();

    return 0;
}
