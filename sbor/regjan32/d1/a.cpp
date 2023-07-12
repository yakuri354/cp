// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2000;

ll mat[maxn][maxn];
ll ps[maxn][maxn];

ll sum_on(ll x1, ll y1, ll x2, ll y2) {
    ll full = 0, back = 0, up = 0, left = 0;
    full = ps[y2][x2];
    if (x1 >= 0)
        left = ps[y2][x1];
    if (y1 >= 0)
        up = ps[y1][x2];
    if (y1 >= 0 && x1 >= 0)
        back = ps[y1][x1];
    return full + back - up - left;
}

bool is_full(ll i, ll j, ll sz) {
    ll i1 = i - sz - 1, j1 = j - sz - 1;
    return sum_on(i1, j1, i, j) == sz * sz;
}

void solve() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            char c = getchar();
            mat[i][j] = c == '#';
        }
        getchar();
    }

    for (ll i = 0; i < n; i++) {
        ll prefrow = 0;
        for (ll j = 0; j < n; j++) {
            prefrow += mat[i][j];
            if (i == 0) {
                ps[i][j] = prefrow;
            } else {
                ps[i][j] = ps[i-1][j] + prefrow;
            }
        }
    }

    vector<pair<ll, pair<ll, ll>>> sqs;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ll lo = 0, hi = min(i, j) + 1;
            if (!mat[i][j]) continue;
            while (hi - lo > 1) {
                ll m = (lo + hi) / 2;
                if (is_full(i, j, m)) lo = m;
                else hi = m;
            }
            sqs.emplace_back(lo, make_pair(i, j));
        }
    }

    sort(sqs.begin(), sqs.end());

    for (auto z : sqs) {
        cout << z.first << " -> " << z.second.first << " " << z.second.second << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
