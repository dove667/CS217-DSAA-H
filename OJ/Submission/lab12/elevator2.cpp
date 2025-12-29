#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
using ll = long long;
using TP = tuple<ll,ll,int>;

inline ll up_cost(ll x, ll y){ return max(0LL, y - x); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    while(T--){
        int n;
        ll f;
        cin >> n >> f;
        vector<pair<ll,ll>> a(n+1); // a[i] = {l_i, r_i}, index from 1..n
        vector<TP> R, L; // R: r >= f; L: r < f
        for(int i=1;i<=n;i++){
            ll l,r; cin >> l >> r;
            a[i] = {l,r};
            if(r >= f) R.emplace_back(l,r,i);
            else L.emplace_back(l,r,i);
        }
        a[0] = {f,f};
        vector<int> order;
        order.reserve(n+1);
        order.push_back(0);

        // Process R: sort by l ascending, pick those increasing pos
        sort(R.begin(), R.end(), [](const TP &x, const TP &y){
            if(get<0>(x) != get<0>(y)) return get<0>(x) < get<0>(y);
            return get<1>(x) < get<1>(y);
        });

        ll pos = f;
        // If some R items have r <= pos, they will be moved to L
        for(auto &t : R){
            ll l = get<0>(t), r = get<1>(t);
            int idx = get<2>(t);
            if(r > pos){
                order.push_back(idx);
                pos = r;
            }else{
                L.emplace_back(l,r,idx);
            }
        }

        // Process L: sort by r descending and append
        sort(L.begin(), L.end(), [](const TP &x, const TP &y){
            if(get<1>(x) != get<1>(y)) return get<1>(x) > get<1>(y);
            return get<0>(x) < get<0>(y);
        });
        for(auto &t : L){
            int idx = get<2>(t);
            order.push_back(idx);
        }

        ll total = 0;
        for(int i=1;i<(int)order.size();++i){
            int cur = order[i];
            int last = order[i-1];
            total += up_cost(a[last].second, a[cur].first);
            total += (a[cur].second - a[cur].first);
        }

        cout << total << '\n';
        for(int i=1;i<(int)order.size();++i){
            if(i>1) cout << ' ';
            cout << order[i];
        }
        cout << '\n';
    }
    return 0;
}
