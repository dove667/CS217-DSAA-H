#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> bfs(int start, const vector<vector<int>>& adj, int n) {
    vector<int> dist(n+1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if(n == 1){
        cout << 0 << "\n";
        return 0;
    }

    // 第一次 BFS（同时检测连通性）
    vector<int> dist1 = bfs(1, adj, n);
    for(int i = 1; i <= n; i++){
        if(dist1[i] == -1){
            cout << -1 << "\n";
            return 0;
        }
    }

    // 找最远点 x
    int x = 1;
    for(int i = 1; i <= n; i++){
        if(dist1[i] > dist1[x]) x = i;
    }

    // 第二次 BFS from x
    vector<int> distX = bfs(x, adj, n);
    int y = x;
    for(int i = 1; i <= n; i++){
        if(distX[i] > distX[y]) y = i;
    }
    int dx = distX[y];

    // 第三次 BFS from y
    vector<int> distY = bfs(y, adj, n);
    int dy = 0;
    for(int i = 1; i <= n; i++){
        dy = max(dy, distY[i]);
    }

    int D = max(dx, dy);

    if(D <= 1){
        cout << 0 << "\n";
        return 0;
    }

    // rounds = ceil(log2(D))
    int rounds = 0;
    int reach = 1;
    while(reach < D){
        reach <<= 1;
        rounds++;
    }

    cout << rounds << "\n";
    return 0;
}
