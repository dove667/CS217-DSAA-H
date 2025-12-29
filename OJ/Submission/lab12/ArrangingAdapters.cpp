#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int num_chargers;
    ll num_sockets;
    if (!(cin >> num_chargers >> num_sockets)) return 0;
    vector<ll> chargers(num_chargers);
    for (int i = 0; i < num_chargers; ++i) cin >> chargers[i];

    if (num_sockets == 1 || num_chargers ==1) { cout <<  1 << '\n'; return 0; }

    sort(chargers.begin(), chargers.end());

    ll inner_sockets = num_sockets - 2;
    if (inner_sockets < 0) inner_sockets = 0;

    ll num = 0;           // sum of used full 3cm-block sockets so far
    ll mp1 = 0, mp2 = 0;  // counts of remainder 1 and remainder 2 among considered chargers
    int placed = 0;
    int limit = num_chargers - 2; // number of elements we can try to put into inner (indices 0..limit-1)
    for (int i = 0; i < limit; ++i) {
        ll charger = chargers[i];
        ll full = charger / 3;
        int rem = static_cast<int>(charger % 3);

        if (rem == 1) ++mp1;
        else if (rem == 2) ++mp2;

        ll formed = min(mp1, mp2);
        ll tmp_mp1 = mp1 - formed;
        ll tmp_mp2 = mp2 - formed;
        ll candidate_needed = num + full + formed + ( (tmp_mp1 + 1) / 2 ) + tmp_mp2;

        if (candidate_needed > inner_sockets) {
            break;
        }
        num += full + formed;
        mp1 = tmp_mp1;
        mp2 = tmp_mp2;
        ++placed;
    }

    ll ans = placed + 2;
    if (ans > num_chargers) ans = num_chargers;
    if (ans > num_sockets) ans = num_sockets;
    cout << ans << '\n';
    return 0;
}
