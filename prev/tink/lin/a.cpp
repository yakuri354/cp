// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
ll a[100001];
ll b[100001];
ll d[100001];
pair<ll, ll> e[100001];
ll f[100001];

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (ll i = 0; i < m; i++) {
        cin >> e[i].first >> e[i].second >> d[i];
        e[i].first--;
        e[i].second--;
    }

    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;

        f[x-1] += 1;
        f[y] -= 1;
    }

    ll s = 0;
    for (ll i = 0; i < m; i++) {
        s += f[i];
        b[e[i].first] += d[i] * s;
        b[e[i].second + 1] -= d[i] * s;
    }

    s = 0;
    for (ll i = 0; i < n; i++) {
        s += b[i];
        cout << a[i] + s << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
