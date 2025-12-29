#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void lcs(vector<vector<int>>& dp, const string& s, const string& t) {
    for (size_t i = 1; i <= s.size(); ++i) {
        for (size_t j = 1; j <= t.size(); ++j) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
}

string backtrack(vector<vector<int>> dp, const string& s, const string& t, int i = -1, int j = -1) {
    if (i == -1) i = static_cast<int>(s.size());
    if (j == -1) j = static_cast<int>(t.size());
    string res;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            res.push_back(s[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(res.begin(), res.end());
    return res;

}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    cin >> s >> t;
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    lcs(dp, s, t);
    string ans = backtrack(dp, s, t);
    cout << ans << "\n";
    return 0;
}