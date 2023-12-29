// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

struct edge {
    ll u, v, w;

    bool operator<(const edge &other) {
        return this->w < other.w;
    }
};

edge a[100000];
ll p[20001];
ll s[20001];

ll leader(ll v) {
    if (p[v] == v) return v;
    return p[v] = leader(p[v]);
}

void unite(ll a, ll b) {
    a = leader(a), b = leader(b);
    if (s[a] > s[b]) swap(a, b);
    s[a] += s[b];
    p[b] = a;
}

void solve() {
    ll n, m, ans = 0;
    cin >> n >> m;

    for (ll i = 1; i <= n; i++) {
        p[i] = i;
        s[i] = 1;
    }

    for (ll i = 0; i < m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].w;
    }

    sort(a, a + m);

    for (ll i = 0; i < m; i++) {
        if (leader(a[i].u) != leader(a[i].v)) {
            unite(a[i].u, a[i].v);
            ans += a[i].w;
        }
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
