#include <bits/stdc++.h>
using namespace std;

int reverse_ops(vector<int>& arr, int val, int heap_size, bool is_max, unordered_map<int, int>& index_map) {
    vector<int> trace;
    int index = index_map[val];  
    int i = heap_size - 1;

    while (arr[i] != val) {
        if ((is_max && arr[i] < val) || (!is_max && arr[i] > val)) {
            trace.push_back(i);
            i = (i - 1) / 2;
        } else return -1;
    }

    // 按路径逆序交换
    for (int k = (int)trace.size() - 1; k >= 0; k--) {
        int j = trace[k];
        swap(arr[index], arr[j]);
        // 同步更新索引表
        index_map[arr[index]] = index;
        index_map[arr[j]] = j;
        index = j;
    }
    return 0;
}

vector<int> solve(int n, const vector<int>& insert_order, vector<int>& final) {
    vector<int> bin;
    bin.reserve(n);
    int heap_size = n;

    // 值 -> 索引表
    unordered_map<int, int> index_map;
    index_map.reserve(n * 2);
    for (int i = 0; i < n; i++)
        index_map[final[i]] = i;

    while (heap_size > 0) {
        int val = insert_order[heap_size - 1];
        int last = final[heap_size - 1];
        if (last != val) {
            bool is_max = (last < val);
            bin.push_back(is_max ? 1 : 0);
            if (reverse_ops(final, val, heap_size, is_max, index_map) == -1)
                return {-1};
        } else {
            bin.push_back(0);
        }
        heap_size--;
    }

    reverse(bin.begin(), bin.end());
    return bin;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> insert_order(n), final(n);
        for (int& x : insert_order) cin >> x;
        for (int& x : final) cin >> x;

        vector<int> res = solve(n, insert_order, final);
        if (res.size() == 1 && res[0] == -1)
            cout << "Impossible\n";
        else {
            for (int i = 0; i < n; i++) {
                if (i) cout << " ";
                cout << res[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
