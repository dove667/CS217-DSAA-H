#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1), radj(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);      // 原图
        radj[y].push_back(x);     // 反图
    }

    int s, t;
    cin >> s >> t;

    // 1. 在反图上，从 t 出发 BFS，找出哪些点能到达 t
    vector<bool> canReachT(n + 1, false);
    queue<int> q;
    q.push(t);
    canReachT[t] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : radj[u]) {   // 在反图上：u <- v
            if (!canReachT[v]) {
                canReachT[v] = true;
                q.push(v);
            }
        }
    }

    // 2. 判断每个点是否为“好点”：所有出边都指向能到达 t 的点
    vector<bool> good(n + 1, true);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (!canReachT[v]) {
                good[u] = false;
                break;
            }
        }
    }

    // 如果 s 或 t 本身就不能到达 t 或不是好点，直接无解
    if (!canReachT[s] || !canReachT[t] || !good[s] || !good[t]) {
        cout << -1;
        return 0;
    }

    // 3. 在原图上 BFS，但只走 good 且 canReachT 的点
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, -1);      // 记录边数距离

    queue<int> q2;
    q2.push(s);
    visited[s] = true;
    dist[s] = 0;

    while (!q2.empty()) {
        int u = q2.front(); q2.pop();
        if (u == t) break;

        for (int v : adj[u]) {
            if (!visited[v] && good[v] && canReachT[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;    // 每条边长度为 1
                q2.push(v);
            }
        }
    }

    if (!visited[t]) {
        cout << -1;
        return 0;
    }

    cout << dist[t];
    return 0;
}
