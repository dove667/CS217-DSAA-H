#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
using namespace std;

struct Edge { int to, w; };
using State = pair<int, int>;  // (key, vertex)

struct MinHeap {
    
    vector<State> h;
    vector<int> pos;                     // vertex -> index in heap, -1 if not present

    explicit MinHeap(int n) : pos(n, -1) {}

    bool empty() const { return h.empty(); }

    void build(const vector<int>& key) {
        int n = static_cast<int>(key.size());
        h.reserve(n);
        for (int v = 0; v < n; ++v) {
            h.emplace_back(key[v], v);
            pos[v] = v;
        }
        for (int i = static_cast<int>(h.size()) / 2 - 1; i >= 0; --i) heapify_down(i);
    }

    State extract_min() {
        State res = h[0];
        swap_nodes(0, static_cast<int>(h.size()) - 1);
        pos[h.back().second] = -1;
        h.pop_back();
        if (!h.empty()) heapify_down(0);
        return res;
    }

    void decrease_key(int vertex, int new_key) {
        int i = pos[vertex];
        if (i == -1) return;  // already removed
        if (new_key >= h[i].first) return;
        h[i].first = new_key;
        heapify_up(i);
    }

private:
    void heapify_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (h[p] <= h[i]) break;
            swap_nodes(i, p);
            i = p;
        }
    }

    void heapify_down(int i) {
        int n = static_cast<int>(h.size());
        while (true) {
            int l = i * 2 + 1, r = i * 2 + 2, smallest = i;
            if (l < n && h[l] < h[smallest]) smallest = l;
            if (r < n && h[r] < h[smallest]) smallest = r;
            if (smallest == i) break;
            swap_nodes(i, smallest);
            i = smallest;
        }
    }

    void swap_nodes(int i, int j) {
        swap(h[i], h[j]);
        pos[h[i].second] = i;
        pos[h[j].second] = j;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 5;
    vector<vector<Edge>> g(n);
    auto add = [&](int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };

    add(0, 1, 2); add(0, 3, 6); add(1, 2, 3);
    add(1, 3, 8); add(1, 4, 5); add(2, 4, 7); add(3, 4, 9);

    const int INF = numeric_limits<int>::max();
    vector<int> dist(n, INF), parent(n, -1);
    vector<bool> in_mst(n, false);
    dist[0] = 0;
    MinHeap pq(n);
    pq.build(dist);

    int mst_weight = 0; vector<tuple<int,int,int>> mst;
    while (!pq.empty()) {
        auto [d, u] = pq.extract_min();
        if (in_mst[u]) continue;  // 已经加入 MST
        in_mst[u] = true;
        if (parent[u] != -1) {
            mst_weight += d;
            mst.emplace_back(parent[u], u, d);
        }

        for (auto e : g[u]) {
            if (!in_mst[e.to] && e.w < dist[e.to]) {
                dist[e.to] = e.w;
                parent[e.to] = u;
                pq.decrease_key(e.to, dist[e.to]);
            }
        }
    }

    cout << "Prim MST weight: " << mst_weight << "\nEdges:\n";
    for (auto [from, to, w] : mst) cout << from << " - " << to << " (" << w << ")\n";
    return 0;
}
