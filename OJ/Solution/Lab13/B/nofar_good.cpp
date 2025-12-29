#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int INF = 10000000;


int main() {
    // input
    int n, m, u, v;
    cin >> n >> m;
    vector< vector<int> > g (n);
    for (int i=0; i<m; i++) {
        cin >> u >> v;
        u--; v--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    //BFS
    vector<int> dist (n, INF);
    int largest_dist = dist[0] = 0;
    int visited = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited++;
        for (int v : g[u]) if (dist[v] == INF) {
            largest_dist = dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    //output
    if (visited < n) {
        cout << -1 << endl;
    } else {
        cout << ceil(log(largest_dist)/log(2))+1 << endl;
    }
    return 0;
}
