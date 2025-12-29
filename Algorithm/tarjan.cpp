#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
public:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;
    int timer;
    std::vector<int> disc, low;
    std::vector<bool> onStack;
    std::stack<int> st;
    std::vector<std::vector<int>> sccList;

    Graph(int v) : vertices(v), adjacencyList(v), timer(0), 
                   disc(v, -1), low(v, -1), onStack(v, false) {}

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
    }

    void tarjan() {
        for (int i = 0; i < vertices; ++i) {
            if (disc[i] == -1) {
                tarjanDFS(i);
            }
        }

        std::cout << "Strongly Connected Components (Tarjan):" << std::endl;
        for (const auto& scc : sccList) {
            std::cout << "SCC: ";
            for (int node : scc) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    void tarjanDFS(int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        onStack[u] = true;

        for (int v : adjacencyList[u]) {
            if (disc[v] == -1) {
                tarjanDFS(v);
                low[u] = std::min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            std::vector<int> scc;
            while (true) {
                int v = st.top();
                st.pop();
                onStack[v] = false;
                scc.push_back(v);
                if (v == u) break;
            }
            sccList.push_back(scc);
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
    g.tarjan();

    return 0;
}
