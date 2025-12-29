#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct KojiLess {
    bool operator()(const string& a, const string& b) const {
        size_t i = 0, n = a.size(), m = b.size();
        while (i < n && i < m && a[i] == b[i]) ++i;
        if (i == n || i == m) return n < m;   // 前缀关系
        return a[i] < b[i];                   // 首个不同位比较
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    sort(a.begin(), a.end(), KojiLess());

    for (auto& s : a) cout << s << '\n';
    return 0;
}