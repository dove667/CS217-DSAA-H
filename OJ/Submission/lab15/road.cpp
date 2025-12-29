#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// belong = -1 表示原图的边
// belong = 0...k-1 表示属于哪个城镇
struct Edge {
    int u, v;
    long long w;
    int belong; 

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    // 优化：记录集合中包含“原本城市”的数量
    vector<int> city_cnt; 
    
    DSU(int size, int n_original) {
        parent.resize(size);
        city_cnt.assign(size, 0);
        iota(parent.begin(), parent.end(), 0);
        
        // 只有原本的 1~n 号节点算作“城市”
        for(int i=1; i<=n_original; ++i) {
            city_cnt[i] = 1; 
        }
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    // 返回合并后集合包含的原始城市数量
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;
        parent[rootY] = rootX;
        city_cnt[rootX] += city_cnt[rootY];
        return true;
    }

    int city_size(int x) {
        return city_cnt[find(x)];
    }
};

vector<Edge> keep_useful_original_edges(int n, vector<Edge> original_edges) {
    sort(original_edges.begin(), original_edges.end());
    DSU dsu(n + 1, n);
    vector<Edge> kept;
    kept.reserve(n - 1);
    for (const auto& e : original_edges) {
        if (dsu.unite(e.u, e.v)) kept.push_back(e);
    }
    return kept;
}

vector<long long> precompute_town_costs(const vector<long long>& town_cost) {
    int k = static_cast<int>(town_cost.size());
    int total_states = 1 << k;
    vector<long long> mask_cost(total_states, 0);
    for (int mask = 1; mask < total_states; ++mask) {
        int bit = __builtin_ctz(mask);
        int prev = mask ^ (1 << bit);
        mask_cost[mask] = mask_cost[prev] + town_cost[bit];
    }
    return mask_cost;
}

long long solve_min_cost(int n, int k, const vector<Edge>& all_edges, const vector<long long>& town_cost) {
    const int total_states = 1 << k;
    auto mask_cost = precompute_town_costs(town_cost);
    long long best = -1;

    for (int mask = 0; mask < total_states; ++mask) {
        long long current = mask_cost[mask];
        if (best != -1 && current >= best) continue;

        DSU dsu(n + k + 1, n);

        for (const auto& edge : all_edges) {
            if (edge.belong != -1 && ((mask >> edge.belong) & 1) == 0) continue;
            if (!dsu.unite(edge.u, edge.v)) continue;

            current += edge.w;
            if (best != -1 && current >= best) break;
            if (dsu.city_size(1) == n) {
                best = (best == -1 ? current : min(best, current));
                break; // 边已按权重排序，后续只会更贵
            }
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<Edge> original_edges;
    original_edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        original_edges.push_back({u, v, w, -1});
    }

    vector<Edge> candidates = keep_useful_original_edges(n, std::move(original_edges));

    vector<long long> town_cost(k);
    for (int i = 0; i < k; ++i) {
        cin >> town_cost[i];
        for (int city = 1; city <= n; ++city) {
            long long w;
            cin >> w;
            candidates.push_back({city, n + 1 + i, w, i});
        }
    }

    sort(candidates.begin(), candidates.end());

    long long ans = solve_min_cost(n, k, candidates, town_cost);
    cout << ans << "\n";

    return 0;
}