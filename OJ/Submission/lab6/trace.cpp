#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

void quickFix(vector<int>& arr, int l, int r, int& count, vector<int>& pos) {
    if (l >= r) return;
    const int mid = (l + r) / 2;
    const int pivotVal = arr[mid];
    int j = mid;
    if (pivotVal <= mid) {
        vector<int> L;
        for (int idx = l; idx <= pivotVal; idx++) {
            if (pos[idx] >= pivotVal) {
                L.push_back(pos[idx]);
            }
        }
        sort(L.begin(), L.end(), greater<>());
        vector<int> R;
        for (int val = l; val <= pivotVal; val++) {
            if (arr[val] >= pivotVal && arr[val] != val) { //不要包含主元
                R.push_back(val);
            }
        }
        if (!R.empty()) {
            for (size_t i = 0; i < R.size(); i++) {
                int x = L[i];
                int y = R[i];
                swap(arr[x], arr[y]);
                swap(pos[arr[x]], pos[arr[y]]);
                cout << "swap " << x << ", " << y << "\n";
                count++;
                j = pivotVal;
            }
        }
    }
    else {
        vector<int> L;
        for (int idx = r; idx >= pivotVal; idx--) {
            if (pos[idx] <= pivotVal) {
                L.push_back(pos[idx]);
            }
        }
        sort(L.begin(), L.end());
        vector<int> R;
        for (int val = r; val >= pivotVal; val--) {
            if (arr[val] <= pivotVal && arr[val] != val) {
                R.push_back(val);
            }
        }
        if (!R.empty()) {
            for (size_t i = 0; i < R.size(); i++) {
                int x = L[i];
                int y = R[i];
                swap(arr[x], arr[y]);
                swap(pos[arr[x]], pos[arr[y]]);
                cout << "swap " << x << ", " << y << "\n";
                count++;
                j = y == pivotVal ? y - 1 : pivotVal - (arr[pivotVal] > pivotVal);
            }
        }
    }
    quickFix(arr, l, j, count, pos);
    quickFix(arr, j + 1, r, count, pos);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n + 1), pos(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            pos[arr[i]] = i;
        }
        int count = 0;
        quickFix(arr, 1, n, count, pos);
        cout << count << "\n";
    }
    return 0;
}
