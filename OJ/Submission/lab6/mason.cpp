#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
const int N = 1e6 + 7;

int n, a[N], pos[N], ans;

void solve(int l, int r) {
    if(l >= r) return;

    int pivot = a[(l + r) >> 1], p = (l + r) >> 1;
    if(pivot - l < r - pivot) {
        std::vector<int> lis;
        for(int i = l; i <= pivot; i++) if(pos[i] >= pivot) lis.push_back(pos[i]);
        std::sort(lis.begin(), lis.end());
        for(int i = l; i <= pivot; i++) if(a[i] >= pivot && a[i] != i) {
            int x = i, y = lis.back();lis.pop_back();
            std::swap(a[x], a[y]), std::swap(pos[a[x]], pos[a[y]]);
            std::cout << "swap " << x << ", " << y << "\n";
            ans++;
        }
        p = pivot;
    } else {
        std::vector<int> lis;
        for(int i = r; i >= pivot; i--) if(pos[i] <= pivot) lis.push_back(pos[i]);
        std::sort(lis.begin(), lis.end(), std::greater<int>());
        for(int i = r; i >= pivot; i--) if(a[i] <= pivot && a[i] != i) {
            int x = i, y = lis.back();lis.pop_back();
            std::swap(a[x], a[y]), std::swap(pos[a[x]], pos[a[y]]);
            std::cout << "swap " << x << ", " << y << "\n";
            ans++, p = x == pivot ? x - 1 : pivot - (a[pivot] > pivot);
        }
    }

    solve(l, p), solve(p + 1, r);
}

void solve() {
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> a[i], pos[a[i]] = i;
    ans = 0, solve(1, n), std::cout << ans << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    int T; std::cin >> T;
    while(T--) solve();
    return 0;
}