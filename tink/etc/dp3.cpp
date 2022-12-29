// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

ll a[100000];
ll d[100000];
ll pos[100000];
ll par[100000];

void solve() {
    ll n, a1, k, b, m;
    cin >> n >> a1 >> k >> b >> m;

    a[0] = a1;
    for (ll i = 1; i < n; i++) {
        a[i] = (k * a[i-1] + b) % m;
    }

    ll t = 0;
    for (ll i = 0; i < n; i++) {
        ll l = upper_bound(d, d + t, a[i]) - d;
        if ((l > 0 && d[l-1] >= a[i]) || (t > l && d[l] <= a[i])) continue;
        pos[l] = i;
        par[i] = l == 0 ? -1 : pos[l-1];
        d[l] = a[i];
        if (l == t) t++;
    }

    vector<ll> ans;
    ll e = pos[t - 1];
    while (e != -1) {
        ans.push_back(a[e]);
        e = par[e];
    }
    cout << t << endl;
    for (ll i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
