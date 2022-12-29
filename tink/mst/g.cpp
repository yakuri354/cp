// #pragma GCC optimize("Ofast")
#include <iomanip>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

const ll maxn = 5000;

void solve() {
    ll n, m;
    cin >> n;
    vector<pair<short, short>> a(n);
    vector<fl> min_v(n, inf);
    vector<bool> used(n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    cin >> m;
    vector<pair<ll, ll>> el(m);

    for (ll i = 0; i < m; i++) {
        cin >> el[i].first >> el[i].second;
        el[i].first--;
        el[i].second--;
    }

    fl ans = 0.0;

    min_v[0] = 0.0;
    for (ll sz = 0; sz < n; sz++) {
        ll v = -1;
        for (ll j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || min_v[j] < min_v[v])) {
                v = j;
            }
        }
        if (v == -1 || min_v[v] == inf) break;

        used[v] = true;
        ans += min_v[v];

        for (ll i = 0; i < n; i++) {
            fl dx = abs(fl(a[i].first) - fl(a[v].first));
            fl dy = abs(fl(a[i].second) - fl(a[v].second));
            min_v[i] = min(min_v[i], sqrt(dx * dx + dy * dy));
        }

        for (ll i = 0; i < m; i++) {
            if (el[i].first == v)
                min_v[el[i].second] = 0;
            if (el[i].second == v)
                min_v[el[i].first] = 0;
        }
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    cout << setprecision(6) << fixed;
    solve();
}
