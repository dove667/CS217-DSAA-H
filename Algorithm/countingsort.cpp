#include <iostream>
#include <vector>
#include <algorithm>

// 计数排序，稳定，支持负数
std::vector<int> countingSort(const std::vector<int>& a) {
    if (a.empty()) return {};

    int n = static_cast<int>(a.size());
    int minv = *std::min_element(a.begin(), a.end());
    int maxv = *std::max_element(a.begin(), a.end());
    int range = maxv - minv + 1;

    std::vector<int> count(range, 0);
    for (int x : a) count[x - minv]++;

    // 前缀和：count[i] 表示 <= i 的数量
    for (int i = 1; i < range; ++i) count[i] += count[i - 1];

    std::vector<int> out(n);
    // 从后向前遍历以保持稳定性
    for (int i = n - 1; i >= 0; --i) {
        int idx = a[i] - minv;
        count[idx]--;
        out[count[idx]] = a[i];
    }
    return out;
}

int main() {
    std::vector<int> data = {4, -1, 3, 0, 3, -1, 2, 4, 0};
    std::cout << "原数组: ";
    for (int x : data) std::cout << x << ' ';
    std::cout << '\n';

    std::vector<int> sorted = countingSort(data);

    std::cout << "排序后: ";
    for (int x : sorted) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}