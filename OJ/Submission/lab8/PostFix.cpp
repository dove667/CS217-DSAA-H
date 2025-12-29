#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            string token;
            cin >> token;
            if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*')) {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                int res = 0;
                if (token[0] == '+') res = a + b;
                else if (token[0] == '-') res = a - b;
                else if (token[0] == '*') res = a * b;
                st.push(res);
            } else {
                st.push(stoi(token));
            }
        }
        if (!st.empty()) {
            cout << st.top() << '\n';
        }
    }
    return 0;
}