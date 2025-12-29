#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const long long INF = 1e18;

struct State {
    long long cost; // 当前花费
    int u;          // 当前所在的节点编号
    int p;          // 当前的档位
};

class MinBinaryHeap {
private:
    vector<State> heap;

    void sift_up(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (heap[parent].cost <= heap[i].cost) break;
            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    void sift_down(size_t i) {
        const size_t n = heap.size();
        while (true) {
            size_t left = i * 2 + 1;
            size_t right = i * 2 + 2;
            size_t smallest = i;

            if (left < n && heap[left].cost < heap[smallest].cost) smallest = left;
            if (right < n && heap[right].cost < heap[smallest].cost) smallest = right;
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    bool empty() const { return heap.empty(); }

    const State& top() const { return heap[0]; }

    void push(const State& s) {
        heap.push_back(s);
        sift_up(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) sift_down(0);
    }
};

struct Edge {
    int to;     // 目标节点
    int weight; // 路的长度
};

void solve() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;

    vector<int> cost_up(k + 1, 0);
    vector<int> cost_down(k + 1, 0);

    for (int i = 1; i < k; ++i) {
        cin >> cost_up[i];
    }

    for (int i = 2; i <= k; ++i) {
        cin >> cost_down[i];
    }

    // 预处理档位跳转前缀和：用于 O(1) 计算 shift(p -> q)
    vector<long long> up_prefix(k + 1, 0), down_prefix(k + 1, 0);
    for (int i = 1; i < k; ++i) {
        up_prefix[i + 1] = up_prefix[i] + cost_up[i];
    }
    for (int i = 2; i <= k; ++i) {
        down_prefix[i] = down_prefix[i - 1] + cost_down[i];
    }

    auto shift_cost = [&](int from_p, int to_p) -> long long {
        if (from_p == to_p) return 0;
        if (from_p < to_p) return up_prefix[to_p] - up_prefix[from_p];
        return down_prefix[from_p] - down_prefix[to_p];
    };
    // 存图：adj[u] 里的第 0 个元素对应“第 1 条路”，第 1 个元素对应“第 2 条路”...
    vector<vector<Edge>> adj(n + 1);

    for (int i = 1; i <= n; ++i) {
        int d;
        cin >> d; // 也就是 di，从 i 出发的路的总数
        for (int j = 0; j < d; ++j) {
            int target, len;
            cin >> target >> len;
            adj[i].push_back({target, len});
        }
    }

    // dist[u][p]：到达节点 u 且档位为 p 的最小花费（稀疏存储，避免 n*k 的巨型数组）
    vector<unordered_map<int, long long>> dist(n + 1);
    auto get_dist = [&](int u, int p) -> long long {
        auto it = dist[u].find(p);
        if (it == dist[u].end()) return INF;
        return it->second;
    };
    
    auto relax = [&](MinBinaryHeap& pq, int u, int p, long long new_cost) {
        auto& mp = dist[u];
        auto it = mp.find(p);
        if (it == mp.end() || new_cost < it->second) {
            mp[p] = new_cost;
            pq.push({new_cost, u, p});
        }
    };

    MinBinaryHeap pq;

    // 起点：在节点 1，初始档位 1，花费 0
    dist[1][1] = 0;
    pq.push({0, 1, 1});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        long long c = current.cost;
        int u = current.u;
        int p = current.p;

        if (c != get_dist(u, p)) continue;

        // 优化：不再一步步升/降档扩展。
        // 从 (u, p) 直接尝试所有可走的第 q 条路：先付 shift_cost(p->q) 再走该路，到达后档位为 q。
        int du = static_cast<int>(adj[u].size());
        for (int q = 1; q <= du; ++q) {
            const Edge& e = adj[u][q - 1];
            long long new_cost = c + shift_cost(p, q) + e.weight;
            relax(pq, e.to, q, new_cost);
        }
    }

    // 输出结果
    for (int i = 1; i <= n; ++i) {
        long long min_cost = INF;

        for (const auto& kv : dist[i]) {
            min_cost = min(min_cost, kv.second);
        }
        
        if (min_cost == INF) cout << -1 << " ";
        else cout << min_cost << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int c;
    if (cin >> c) {
        solve();
    }
    return 0;
}