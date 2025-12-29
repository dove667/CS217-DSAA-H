#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

void simulate(std::vector<std::vector<int>>& dom, std::vector<int>& buc, int m1) {
    //给dom按照到来时间排序
    std::sort(dom.begin(), dom.end(), [](const std::vector<int>& a, const std::vector<int>& b){
        return a[0] < b[0];
    });
    // 维护两个最小堆：
    // available_bridges：存放空闲的桥梁编号
    // busy_bridges：形式为 (departure_time, bridge_number)，按 departure_time (离开时间) 排序
    std::priority_queue<int, std::vector<int>, std::greater<>> available_bridges;
    for (int i = 1; i <= m1; ++i) available_bridges.push(i);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> busy_bridges;
    // 处理航班
    for (const auto& flight : dom) {
        int arrival = flight[0];
        int departure = flight[1];
        // 释放已离开的桥梁
        while (!busy_bridges.empty() && busy_bridges.top().first <= arrival) {
            available_bridges.push(busy_bridges.top().second);
            busy_bridges.pop();
        }
        if (!available_bridges.empty()) {
            int bridge = available_bridges.top();
            available_bridges.pop();
            busy_bridges.emplace(departure, bridge);
            buc[bridge] += 1;
        }
    }
}
int solve(std::vector<std::vector<int>>& dom, std::vector<std::vector<int>>& inter, int m1, int m2, int n) {
    std::vector<int> buc1(m1 + 1, 0);std::vector<int> buc2(m2 + 1, 0);
    simulate(dom, buc1, m1);
    simulate(inter, buc2, m2);

    std::vector<int> f(n + 1, 0);
    std::vector<int> g(n + 1, 0);
    // 计算 f[k]
    for (int k = 1; k <= n; ++k) {
        f[k] = f[k - 1];
        if (k <= m1) {
            f[k] += buc1[k];
        }
    }
    // 计算 g[k]
    for (int k = 1; k <= n; ++k) {
        g[k] = g[k - 1];
        if (k <= m2) {
            g[k] += buc2[k];
        }
    }
    int max = 0;
    for (int k = 0; k <= n; ++k) {
        int cur = f[k] + g[n - k];
        if (cur > max) max = cur;
    }
    return max;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;
    std::vector<std::vector<int>> dom(m1, std::vector<int>(2));
    for (int i = 0; i < m1; ++i) {
        std::cin >> dom[i][0] >> dom[i][1];
    }
    std::vector<std::vector<int>> inter(m2, std::vector<int>(2));
    for (int i = 0; i < m2; ++i) {
        std::cin >> inter[i][0] >> inter[i][1];
    }

    int max = solve(dom, inter, m1, m2, n);
    std::cout << max;
    return 0;
}