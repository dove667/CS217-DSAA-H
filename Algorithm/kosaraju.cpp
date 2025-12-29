#include <iostream>
#include <vector>
#include <stack>

class Graph {
public:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;
    std::vector<std::vector<int>> reverseAdjacencyList;

    Graph(int v) : vertices(v), adjacencyList(v), reverseAdjacencyList(v) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        reverseAdjacencyList[v].push_back(u);
    }

    void kosaraju() {
        std::stack<int> st;
        std::vector<bool> visited(vertices, false);

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i]) {
                fillOrder(i, visited, st);
            }
        }

        visited.assign(vertices, false);
        std::cout << "Strongly Connected Components:" << std::endl;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (!visited[u]) {
                std::cout << "SCC: ";
                dfsReverse(u, visited);
                std::cout << std::endl;
            }
        }
    }

private:
    void fillOrder(int u, std::vector<bool>& visited, std::stack<int>& st) {
        visited[u] = true;

        for (int neighbor : adjacencyList[u]) {
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, st);
            }
        }

        st.push(u);
    }

    void dfsReverse(int u, std::vector<bool>& visited) {
        visited[u] = true;
        std::cout << u << " ";

        for (int neighbor : reverseAdjacencyList[u]) {
            if (!visited[neighbor]) {
                dfsReverse(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 0);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 4);
    g.addEdge(6, 7);

    std::cout << "Graph edges: 0->1, 1->2, 2->3, 2->4, 3->0, 4->5, 5->6, 6->4, 6->7" << std::endl;
    g.kosaraju();

    return 0;
}
