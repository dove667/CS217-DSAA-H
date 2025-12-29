#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
using namespace std;

struct Edge { int to, w; };
using State = pair<int, int>; // (dist, node)

struct MinHeap {
    vector<State> h;      // 堆数组
    vector<int> pos;      // 节点 -> 堆下标

    explicit MinHeap(int n) : h(), pos(n, -1) {}

    void build(const vector<int> &dist) {
        h.reserve(dist.size());
        for (int i = 0; i < static_cast<int>(dist.size()); ++i) {
            h.emplace_back(dist[i], i);
            pos[i] = i;
        }
        for (int i = static_cast<int>(h.size()) / 2 - 1; i >= 0; --i) heapify_down(i);
    }

    bool empty() const { return h.empty(); }

    State extract_min() {
        State ret = h[0];
        swap_nodes(0, static_cast<int>(h.size()) - 1);
        pos[h.back().second] = -1;
        h.pop_back();
        if (!h.empty()) heapify_down(0);
        return ret;
    }

    void decrease_key(int node, int new_dist) {
        int i = pos[node];
        if (i == -1) return; // 已经被弹出
        if (new_dist >= h[i].first) return; // 不是更优
        h[i].first = new_dist;
        heapify_up(i);
    }

private:
    void heapify_down(int i) {
        int n = static_cast<int>(h.size());
        while (true) {
            int l = i * 2 + 1, r = i * 2 + 2, smallest = i;
            if (l < n && h[l].first < h[smallest].first) smallest = l;
            if (r < n && h[r].first < h[smallest].first) smallest = r;
            if (smallest == i) break;
            swap_nodes(i, smallest);
            i = smallest;
        }
    }

    void heapify_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (h[p].first <= h[i].first) break;
            swap_nodes(i, p);
            i = p;
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

    int n = 6;
    vector<vector<Edge>> edges(n);
    auto add = [&](int u, int v, int w) {
        edges[u].push_back({v, w});
    };

    add(0, 1, 7); add(0, 2, 9); add(0, 5, 14);
    add(1, 2, 10); add(1, 3, 15);
    add(2, 3, 11); add(2, 5, 2);
    add(3, 4, 6);
    add(4, 5, 9);

    const int INF = 1'000'000'000; // 避免溢出的足够大值
    vector<int> dist(n, INF);
    dist[0] = 0;
    MinHeap pq(n);
    pq.build(dist);

    while (!pq.empty()) {
        auto [d, u] = pq.extract_min();
        for (auto e : edges[u]) {
            if (dist[u] + e.w < dist[e.to]) {
                dist[e.to] = dist[u] + e.w;
                pq.decrease_key(e.to, dist[e.to]);
            }
        }
    }

    cout << "Dijkstra distances from 0:\n";
    for (int i = 0; i < n; ++i) cout << "0 -> " << i << ": " << dist[i] << "\n";
    return 0;
}
