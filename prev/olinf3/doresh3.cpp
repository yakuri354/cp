#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAX_N = 1000;

ll a[MAX_N][MAX_N];

vector<tuple<ll, ll, ll>> path;
queue<pair<ll, ll>> q;

ll N,M;

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i + 1 < N; i++)
        for (int j = 0; j + 1 < M; ++j)
            if (a[i][j] == a[i][j + 1] && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 1][j + 1])
                q.emplace(i, j);

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        ll com = -1;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                ll z = a[y+i][x+j];
                if (z == -1) continue;
                if (com == -1) com = z;
                else if (z != com) goto next;
            }
        }

        if (com == -1) continue;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                a[y+i][x+j] = -1;

        for (int i = -1; i < 2; ++i) {
            if (y + i < 0 || y + i + 1 >= N) continue;
            for (int j = -1; j < 2; ++j) {
                if (x + j < 0 || x + j + 1 >= M) continue;
                q.emplace(y + i, x + j);
            }
        }

        path.emplace_back(y, x, com);
        next:;
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (a[i][j] != -1) {
                cout << -1 << endl;
                return 0;
            }

    cout << path.size() << "\n";
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        auto [a, b, c] = *it;
        cout << a + 1 << " " << b + 1 << " " << c << "\n";
    }
}