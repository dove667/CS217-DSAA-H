#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll s;
    if (!(cin >> n >> s)) return 0;

    // 下标从 1 开始，方便处理前缀和
    vector<ll> t(n + 1), c(n + 1);
    vector<ll> sumT(n + 1, 0); // 时间的前缀和
    vector<ll> sumC(n + 1, 0); // 费用系数的前缀和

    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        sumT[i] = sumT[i - 1] + t[i];
        sumC[i] = sumC[i - 1] + c[i];
    }

    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        // 枚举上一批次的结束位置 j
        // 当前批次就是从 j+1 到 i (例如：j=2, i=4, 当前批次就是 {3, 4})
        for (int j = 0; j < i; ++j) {

            // 核心逻辑：费用提前计算
            // 1. 这一批次实际消耗的时间 = 启动时间 S + (任务 j+1 到 i 的时间和)
            ll current_batch_duration = s + (sumT[i] - sumT[j]);

            // 2. 谁会因为这一批次的时间而产生等待成本？
            //    答案是：这一批次里的任务，以及 *后面所有的任务*。
            //    也就是从 j+1 到 N 的所有任务。
            ll affected_cost_sum = sumC[n] - sumC[j];

            // 3. 这一批次造成的总成本增量
            ll cost_increment = current_batch_duration * affected_cost_sum;

            // 状态转移
            dp[i] = min(dp[i], dp[j] + cost_increment);
        }
    }

    // 输出最终结果
    cout << dp[n] << "\n";

    return 0;
}