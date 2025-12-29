#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN ((int) 1e5)
using namespace std;

int n, V[MAXN + 10], A[MAXN + 10];
char ans[MAXN + 10];

bool gao(int i) {
    int flag = -1, j = i;
    vector<int> vec;

    while (j > 0) {
        vec.push_back(j);
        if (A[j] == V[i]) {
            if (j / 2 > 0) {
                if (A[j / 2] > A[j]) {
                    if (flag == 0) return false;
                    flag = 1;
                } else if (A[j / 2] < A[j]) {
                    if (flag == 1) return false;
                    flag = 0;
                }
            }
            break;
        } else if (A[j] > V[i]) {
            if (flag == 1) return false;
            flag = 0;
        } else {
            if (flag == 0) return false;
            flag = 1;
        }
        j >>= 1;
    }
    if (j == 0) return false;

    if (flag == -1) flag = 0;
    ans[i] = flag + '0';
    while (vec.size() > 1) {
        swap(A[vec.back()], A[vec[vec.size() - 2]]);
        vec.pop_back();
    }
    return true;
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &V[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);

    ans[n + 1] = 0;
    for (int i = n; i; i--) if (!gao(i)) { printf("Impossible\n"); return; }
    printf("%s\n", ans + 1);
}

int main() {
    int tcase; scanf("%d", &tcase);
    while (tcase--) solve();
    return 0;
}
