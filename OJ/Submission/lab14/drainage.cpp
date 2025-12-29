#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

typedef __int128_t int128;

int128 gcd(int128 a, int128 b) {
    return b == 0 ? a : gcd(b, a % b);
}

void print_int128(int128 x) {
    if (x == 0) {
        cout << "0";
        return;
    }
    if (x > 9) print_int128(x / 10);
    cout << (char)(x % 10 + '0'); 
}

struct Fraction {
    int128 p, q; // p是分子，q是分母

    Fraction(int128 _p = 0, int128 _q = 1) {
        if (_q == 0) _q = 1; // 防止分母为0
        p = _p;
        q = _q;
    }

    void add(Fraction other) {
        if (other.p == 0) return; // 加0不需要处理
        if (p == 0) { // 如果自己是0，直接等于对方
            p = other.p;
            q = other.q;
            return;
        }
        
        // 通分
        int128 new_p = p * other.q + other.p * q;
        int128 new_q = q * other.q;

        // 化简
        int128 common = gcd(new_p, new_q);
        p = new_p / common;
        q = new_q / common;
    }

    // 分数
    void divide(int k) {
        q = q * k;
        int128 common = gcd(p, q);
        p /= common;
        q /= common;
    }

    void print() {
        print_int128(p);
        cout << " ";
        print_int128(q);
        cout << "\n";
    }
};

void topologicalSortDFSUtil(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st);
stack<int> topologicalSortDFS(int n, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m; 
    
    vector<vector<int>> adj(n + 1);
    vector<int> outdegree(n + 1, 0); 

    for (int i = 1; i <= n; i++) {
        int d; 
        cin >> d;
        outdegree[i] = d; // 记录出度
        while(d--) {
            int v; 
            cin >> v;
            adj[i].push_back(v);
        }
    }

    // 1. 拓扑排序
    vector<bool> visited(n + 1, false);
    stack<int> st;
    st = topologicalSortDFS(n, adj, visited, st);

    // 2. 初始化水量
    vector<Fraction> water(n + 1);
    
    for(int i = 1; i <= m; ++i) {
        water[i] = Fraction(1, 1);
    }

    // 3. 按照拓扑序进行水量传播
    while(!st.empty()){
        int u = st.top();
        st.pop();

        if (water[u].p > 0 && outdegree[u] > 0) {
            Fraction flow = water[u];
            flow.divide(outdegree[u]);

            for (int v : adj[u]) {
                water[v].add(flow);
            }
        }
    }

    // 4. 输出结果
    for (int i = 1; i <= n; i++) {
        if (outdegree[i] == 0) {
            water[i].print();
        }
    }
    return 0;
}

void topologicalSortDFSUtil(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int neighbor : adj[u]) {
        if (!visited[neighbor]) {
            topologicalSortDFSUtil(neighbor, adj, visited, st);
        }
    }
    st.push(u);
}

stack<int> topologicalSortDFS(int n, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            topologicalSortDFSUtil(i, adj, visited, st);
        }
    }
    return st;
}