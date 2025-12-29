#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent, rankv;
    explicit DSU(int n) : parent(n), rankv(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Sample graph: 0-based nodes
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {1, 0, 4}, {2, 0, 4},
        {2, 1, 2}, {2, 3, 3}, {2, 5, 2}, {2, 4, 4}, {3, 2, 3},
        {3, 4, 3}, {4, 2, 4}, {4, 3, 3}, {5, 2, 2}, {5, 4, 3}
    };

    DSU dsu(n);
    int mst_weight = 0;
    vector<Edge> mst;

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            mst_weight += e.w;
        }
    }

    cout << "Kruskal MST weight: " << mst_weight << "\nEdges:\n";
    for (auto& e : mst) {
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";
    }
    return 0;
}
