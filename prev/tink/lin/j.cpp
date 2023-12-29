// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 5010;
bool in[maxn][maxn];
ll d[maxn][maxn];

void solve() {
    ll n, m, ans;
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> in[i][j];
            in[i][j] ^= 1;
        }
    }

    for (ll i = 0; i < m; i++) {
        d[0][i] = in[0][i];
    }

    for (ll i = 1; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            d[i][j] = in[i][j] * (d[i-1][j] + 1);
        }
    }

    ll ans2 = 0;
    for (ll x = 0; x < n; x++) {
        ll *a = d[x];
        ans = a[0];

        stack<pair<ll, ll>> s;
        s.push({0, -1});
        for (ll i = 0; i < m; i++) {
            while (a[i] <= s.top().first && s.size() > 1) {
                auto [top, ti] = s.top();
                s.pop();

                ans = max(ans, (i - s.top().second - 1) * top);
            }
            if (a[i] == 0) s.pop();
            if (a[i] == 0 || a[i] > s.top().first) {
                s.emplace(a[i], i);
            }
        }

        while (s.size() > 1) {
            auto [top, ti] = s.top();
            s.pop();

            ans = max(ans, (m - s.top().second - 1) * top);
        }
        ans2 = max(ans, ans2);
    }
    cout << ans2 << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
