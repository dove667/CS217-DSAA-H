#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

// 基数 2^8 = 256，每次按 1 字节做稳定计数排序
static std::vector<uint32_t> countingSortByByte(const std::vector<uint32_t>& a, int shift) {
    if (a.empty()) return {};
    int n = static_cast<int>(a.size());
    std::vector<int> count(256, 0);
    for (uint32_t v : a) {
        int digit = static_cast<int>((v >> shift) & 0xFFu);
        count[digit]++;
    }
    for (int i = 1; i < 256; ++i) count[i] += count[i - 1];
    std::vector<uint32_t> out(n);
    for (int i = n - 1; i >= 0; --i) {
        int digit = static_cast<int>((a[i] >> shift) & 0xFFu);
        count[digit]--;
        out[count[digit]] = a[i];
    }
    return out;
}

// 支持有符号 int：通过按位异或 0x80000000u 进行有序映射
std::vector<int> radixSort(const std::vector<int>& a) {
    if (a.empty()) return {};

    std::vector<uint32_t> data;
    data.reserve(a.size());
    for (int x : a) data.push_back(static_cast<uint32_t>(x) ^ 0x80000000u);

    // 32 位 int 固定 4 轮（每轮 8 位）
    for (int shift = 0; shift < 32; shift += 8) {
        data = countingSortByByte(data, shift);
    }

    std::vector<int> res;
    res.reserve(data.size());
    for (uint32_t v : data) res.push_back(static_cast<int>(v ^ 0x80000000u));
    return res;
}
int main() {
    auto printVec = [](const std::vector<int>& v, const char* name) {
        std::cout << name << ":";
        for (int x : v) std::cout << ' ' << x;
        std::cout << '\n';
    };

    std::vector<int> a1 = {170, 45, 75, 90, 802, 24, 2, 66};
    std::vector<int> a2 = {3, 3, 2, 1, 0, 2, 5, 5}; // 重复与 0
    std::vector<int> a3 = {}; // 空数组
    std::vector<int> a4 = {1000, 5, 300, 12, 9999, 7}; // 不同位数

    printVec(a1, "input1");
    printVec(radixSort(a1), "radix1");

    printVec(a2, "input2");
    printVec(radixSort(a2), "radix2");

    printVec(a3, "input3");
    printVec(radixSort(a3), "radix3");

    printVec(a4, "input4");
    printVec(radixSort(a4), "radix4");

    return 0;
}
