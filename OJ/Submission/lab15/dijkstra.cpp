#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Edge { int to; long long w; };
using State = pair<long long, int>; // (dist, node)

struct MinHeap {
    vector<State> h;      // 堆数组
    vector<int> pos;      // 节点 -> 堆下标

    explicit MinHeap(int n) : h(), pos(n, -1) {}

    void build(const vector<long long> &dist) {
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

    void decrease_key(int node, long long new_dist) {
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

    int n = 0;int m = 0;int s = 0;int t = 0;
    cin >> n >> m >> s >> t;
    
    vector<vector<Edge>> edges(n);
    auto add = [&](int u, int v, long long w) {
        edges[u].push_back({v, w});
    };

    for (int i = 0; i < m; ++i) {
        int u, v; long long w;
        cin >> u >> v >> w;
        add(u, v, w);
    }

    const long long INF = numeric_limits<long long>::max(); 
    vector<long long> dist(n, INF);
    vector<int> prev(n, -1);      // 记录前驱节点，支持路径回溯
    dist[s] = 0;
    MinHeap pq(n);
    pq.build(dist);

    while (!pq.empty()) {
        auto [d, u] = pq.extract_min();
        if (d == INF) break; // 剩余节点不可达
        if (u == t) break; 
        for (auto e : edges[u]) {
            if (dist[u] + e.w < dist[e.to]) {
                dist[e.to] = dist[u] + e.w;
                prev[e.to] = u;
                pq.decrease_key(e.to, dist[e.to]);
            }
        }
    }

    if (dist[t] == INF) {
        cout << -1;
        return 0;
    }


    vector<int> path;
    for (int v = t; v != -1; v = prev[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << dist[t] << " " << path.size() - 1 << "\n";
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cout << path[i] << " " << path[i+1] << "\n";
    }
    return 0;
}
