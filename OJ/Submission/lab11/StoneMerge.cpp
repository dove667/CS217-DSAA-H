#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 使用 long long 防止结果溢出，因为费用可能是时间*系数，数值较大
typedef long long ll;

int main() {
    // 优化 I/O 效率，这在算法竞赛中是个好习惯
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll s;
    if (!(cin >> n >> s)) return 0;

    vector<ll> t(n + 1), c(n + 1);
    vector<ll> sumT(n + 1, 0), sumC(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        // 计算前缀和
        sumT[i] = sumT[i - 1] + t[i];
        sumC[i] = sumC[i - 1] + c[i];
    }

    // dp[i] 表示处理完前 i 个任务的最小花费
    // 初始化为一个很大的数
    vector<ll> dp(n + 1, 1e18); // 1e18 足 够大了
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        // 枚举上一批次的结束点 j
        // 也就是当前批次是 [j+1, i]
        for (int j = 0; j < i; ++j) {
            // 当前这一批次消耗的时间（启动时间 + 任务执行时间）
            ll currentBatchTime = s + (sumT[i] - sumT[j]);

            // "费用提前计算"技巧：
            // 这段时间会让从 j+1 开始直到 N 的所有任务都等待
            // 所以成本 = 时间 * (sumC[N] - sumC[j])
            ll cost = currentBatchTime * (sumC[n] - sumC[j]);

            dp[i] = min(dp[i], dp[j] + cost);
        }
    }

    cout << dp[n] << "\n";

    return 0;
}