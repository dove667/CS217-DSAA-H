#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, m;
    if (!(cin >> n >> p >> m)) return 0;

    vector<vector<int>> A(n, vector<int>(p));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            ll x; cin >> x;
            A[i][j] = int((x % MOD + MOD) % MOD);
        }
    }
    vector<vector<int>> C(n, vector<int>(m, 0));

    for (int k = 0; k < p; ++k) {
        vector<int> Brow(m);
        for (int j = 0; j < m; ++j) {
            ll x; cin >> x;
            Brow[j] = int((x % MOD + MOD) % MOD);
        }

        for (int i = 0; i < n; ++i) {
            int aik = A[i][k];
            if (aik == 0) continue; 
            for (int j = 0; j < m; ++j) {
                int prod = int((1LL * aik * Brow[j]) % MOD);
                int sum = C[i][j] + prod;
                if (sum >= MOD) sum -= MOD;
                C[i][j] = sum;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) cout << ' ';
            cout << C[i][j];
        }
        cout << '\n';
    }
    return 0;
}
