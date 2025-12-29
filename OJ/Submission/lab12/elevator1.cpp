#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<tuple<int,int,ll>> groups; // (floor, weight, count)
        groups.reserve(n);
        for (int i = 0; i < n; ++i) {
            ll c;
            int w, f;
            cin >> c >> w >> f;
            groups.emplace_back(f, w, c);
        }
        if (groups.empty()) { cout << 0 << '\n'; continue; }

        // 按照floor降序
        sort(groups.begin(), groups.end(), [](const auto &A, const auto &B){
            return get<0>(A) > get<0>(B);
        });

        ll totalCost = 0;
        ll spareOne = 0;
        ll spareTwo = 0;

        int idx = 0;
        while (idx < n) {
            int floor = get<0>(groups[idx]);
            ll cnt1 = 0, cnt2 = 0;
            // 一次聚合相同floor
            while (idx < n && get<0>(groups[idx]) == floor) {
                int w = get<1>(groups[idx]);
                ll c = get<2>(groups[idx]);
                if (w == 1) cnt1 += c;
                else cnt2 += c;
                ++idx;
            }
            // 优先处理weight2：使用spare2，用完了开新电梯
            if (spareTwo >= cnt2) {
                spareTwo -= cnt2;
                cnt2 = 0;
            } else {
                cnt2 -= spareTwo;
                spareTwo = 0;
                ll cap2 = k / 2;
                ll fullRides = cnt2 / cap2;

                if (fullRides > 0) {
                    totalCost += fullRides * static_cast<ll>(floor);
                    cnt2 -= fullRides * cap2;
                }
                if (cnt2 > 0) {
                    totalCost += floor;
                    ll used2 = cnt2;
                    ll leftover = k - used2 * 2;
                    if (leftover >= 2) spareTwo += leftover / 2;
                    if (leftover % 2 == 1) spareOne += 1;
                    cnt2 = 0;
                }
            }
            // 处理weight1：使用spare1，用完了尽量用spare2凑对，再开新电梯
            if (cnt1 > 0) {
                if (spareOne >= cnt1) {
                    spareOne -= cnt1;
                    cnt1 = 0;
                } else {
                    cnt1 -= spareOne;
                    spareOne = 0;
                    if (spareTwo > 0) {
                        ll usePairs = min(spareTwo, cnt1 / 2);
                        cnt1 -= usePairs * 2;
                        spareTwo -= usePairs;
                        if (cnt1 > 0 && spareTwo > 0) {
                            spareTwo -= 1;
                            spareOne += 1;
                            cnt1 -= 1;
                        }
                    }
                    if (cnt1 > 0) {
                        ll fullRides1 = cnt1 / k;
                        if (fullRides1 > 0) {
                            totalCost += fullRides1 * static_cast<ll>(floor);
                            cnt1 -= fullRides1 * k;
                        }
                        if (cnt1 > 0) {
                            totalCost += floor;
                            ll used1 = cnt1;
                            ll leftover = k - used1;
                            if (leftover >= 2) spareTwo += leftover / 2;
                            if (leftover % 2 == 1) spareOne += 1;
                            cnt1 = 0;
                        }
                    }
                }
            }
        }
        cout << totalCost << '\n';
    }
    return 0;
}
