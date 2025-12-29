#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// N=250，我们需要 250 个位。
// 一个 unsigned long long (u64) 有 64 位。
// 250 / 64 = 3.9，所以我们需要 4 个 u64 来表示一行。
const int N_CHUNKS = 4; 
const int MAXN = 256;

// 使用原生 u64 数组代替 vector<bool> 或 bitset，方便手动操作位
// g[u][k] 表示第 u 个点的第 k 块位图
unsigned long long adj[MAXN][N_CHUNKS]; 
unsigned long long rev_adj[MAXN][N_CHUNKS];
unsigned long long visited[N_CHUNKS]; // 全局访问标记

stack<int> st;
int n, m;

// 设置某一位为 1
inline void set_bit(unsigned long long bitmap[], int pos) {
    bitmap[pos / 64] |= (1ULL << (pos % 64));
}
// 翻转某一位
inline void flip_bit(unsigned long long bitmap[], int pos) {
    bitmap[pos / 64] ^= (1ULL << (pos % 64));
}
// 检查某一位是否为 1
inline bool check_bit(unsigned long long bitmap[], int pos) {
    return (bitmap[pos / 64] >> (pos % 64)) & 1ULL;
}

void dfs1(int u) {
    set_bit(visited, u);
    
    for (int k = 0; k < N_CHUNKS; ++k) {
        while (true) {
            unsigned long long mask = adj[u][k] & ~visited[k];
            if (mask == 0) break;
            
            // __builtin_ctzll 返回二进制末尾 0 的个数，即第一个 1 的位置
            int bit_idx = __builtin_ctzll(mask); 
            int v = k * 64 + bit_idx;
            
            if (v < n) {
                dfs1(v);
            }
        }
    }
    st.push(u);
}

void dfs2(int u, int& cnt) {
    set_bit(visited, u);
    cnt++;
    
    for (int k = 0; k < N_CHUNKS; ++k) {
        while (true) {
            unsigned long long mask = rev_adj[u][k] & ~visited[k];
            if (mask == 0) break;
            
            int bit_idx = __builtin_ctzll(mask);
            int v = k * 64 + bit_idx;
            
            if (v < n) {
                dfs2(v, cnt);
            }
        }
    }
}

long long solve() {
    memset(visited, 0, sizeof(visited));
    while(!st.empty()) st.pop();

    // First Pass
    for (int i = 0; i < n; ++i) {
        if (!check_bit(visited, i)) {
            dfs1(i);
        }
    }

    // Second Pass
    memset(visited, 0, sizeof(visited));
    long long total_pairs = 0;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (!check_bit(visited, u)) {
            int cnt = 0;
            dfs2(u, cnt);
            total_pairs += (long long)cnt * (cnt - 1) / 2;
        }
    }
    return total_pairs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    memset(adj, 0, sizeof(adj));
    memset(rev_adj, 0, sizeof(rev_adj));

    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < n; ++j) {
            if (line[j] == '1') {
                set_bit(adj[i], j);
                set_bit(rev_adj[j], i);
            }
        }
    }

    while (m--) {
        int k;
        cin >> k;
        while (k--) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            flip_bit(adj[u], v);
            flip_bit(rev_adj[v], u);
        }
        cout << solve() << "\n";
    }
    return 0;
}