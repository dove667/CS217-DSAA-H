#include <bits/stdc++.h>
using namespace std;

struct Player {
    int id;
    int score;
    int power;
};

inline bool cmp(const Player &a, const Player &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}

void play(vector<Player> &players, vector<Player> &winners, vector<Player> &losers) {
    winners.clear();
    losers.clear();
    int n = players.size() / 2;
    for (int i = 0; i < n; i++) {
        Player p1 = players[2 * i];
        Player p2 = players[2 * i + 1];
        if (p1.power < p2.power) {
            p2.score++;
            winners.push_back(p2);
            losers.push_back(p1);
        } else {
            p1.score++;
            winners.push_back(p1);
            losers.push_back(p2);
        }
    }
}

void merge_linear(vector<Player> &players, const vector<Player> &winners, const vector<Player> &losers) {
    players.clear();
    players.reserve(winners.size() + losers.size());
    int i = 0, j = 0;
    while (i < (int)winners.size() && j < (int)losers.size()) {
        if (cmp(winners[i], losers[j])) players.push_back(winners[i++]);
        else players.push_back(losers[j++]);
    }
    while (i < (int)winners.size()) players.push_back(winners[i++]);
    while (j < (int)losers.size()) players.push_back(losers[j++]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, q;
    cin >> n >> r >> q;

    vector<int> S(2 * n), W(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> S[i];
    for (int i = 0; i < 2 * n; i++) cin >> W[i];

    vector<Player> players(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        players[i] = {i + 1, S[i], W[i]};
    }

    sort(players.begin(), players.end(), cmp);

    vector<Player> winners, losers;
    winners.reserve(n);
    losers.reserve(n);

    for (int round = 0; round < r; round++) {
        play(players, winners, losers);
        merge_linear(players, winners, losers); // O(n)
    }

    cout << players[q - 1].id << "\n";
    return 0;
}
