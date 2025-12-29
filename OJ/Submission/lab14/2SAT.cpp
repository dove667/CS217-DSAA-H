#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
vector<int> adj[MAXN];
vector<int> rev_adj[MAXN];
stack<int> order;
int scc[MAXN];          // 记录每个点属于哪个 SCC ID
bool visited[MAXN];
int scc_cnt = 0;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v);
    }
    order.push(u);
}

void dfs2(int u) {
    scc[u] = scc_cnt;
    for (int v : rev_adj[u]) {
        if (!scc[v]) {
            dfs2(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string p_str, cnf_str;
    int num_var, num_clause;
    
    cin >> p_str >> cnf_str >> num_var >> num_clause;

    // 变量 1..N  -> 节点 1..N
    // 变量 -1..-N -> 节点 N+1..2N
    auto get_idx = [&](int val) {
        if (val > 0) return val;
        return num_var + (-val);
    };

    // 1. 建图
    for (int i = 0; i < num_clause; ++i) {
        int a, b, end_mark;
        cin >> a >> b >> end_mark;
        
        int u = get_idx(a);
        int v = get_idx(b);
        
        // 逻辑：a V b  <=>  -a -> b  AND  -b -> a
        int neg_a = (a > 0) ? a + num_var : -a;
        int neg_b = (b > 0) ? b + num_var : -b;

        adj[neg_a].push_back(v);
        adj[neg_b].push_back(u);
        
        rev_adj[v].push_back(neg_a);
        rev_adj[u].push_back(neg_b);
    }

    // 2. Kosaraju 第一遍：确定顺序
    int total_nodes = 2 * num_var;
    for (int i = 1; i <= total_nodes; ++i) {
        if (!visited[i]) dfs1(i);
    }

    // 3. Kosaraju 第二遍：染颜色 (找 SCC)
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!scc[u]) {
            scc_cnt++; // 新家族
            dfs2(u);
        }
    }
    
    // 4. 判定是否有解
    bool satisfiable = true;
    for (int i = 1; i <= num_var; ++i) {
        // 如果 x 和 -x 在同一个 SCC 里，无解
        if (scc[i] == scc[i + num_var]) {
            satisfiable = false;
            break;
        }
    }

    if (satisfiable) {
        cout << "s SATISFIABLE" << '\n' << 'v' << ' ';
        // 如果需要输出解，可以根据拓扑序 (SCC ID 大小)
        // 笔记里提到：取拓扑序靠后的为真。
        // 在 Kosaraju 中，scc_id 是按逆拓扑序生成的（先找到的是源头 SCC，标号小）
        // 实际上：Kosaraju 找 SCC 的顺序就是拓扑逆序。
        // 所以 scc_id[x] < scc_id[-x] => x 在拓扑序靠后 => x = 1 (不同实现略有差异，通常比较 scc 值即可)
        for (int i = 1; i <= num_var; ++i) {
            if (scc[i] > scc[i + num_var]) {
                cout << i << " ";
            } else {
                cout << -i << " ";
            }
        }
        cout << 0;
    } else {
        cout << "s UNSATISFIABLE";
    }

    return 0;
}