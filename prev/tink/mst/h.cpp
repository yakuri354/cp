// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 50000;
const ll maxm = 100000;
const ll maxk = 150000;

struct qr {
    char t;
    ll u, v;
};

ll yrmom[maxn];
ll sz[maxn];
qr qs[maxk];
ll qa[maxk];

ll ldr(ll v) {
    return yrmom[v] == v ? v : yrmom[v] = ldr(yrmom[v]);
}

void unite(ll a, ll b) {
    a = ldr(a), b = ldr(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    yrmom[b] = a;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    for (ll i = 0; i < n; i++) {
        yrmom[i] = i;
        sz[i] = 1;
    }
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
    }

    for (ll i = 0; i < k; i++) {
        string qt;
        cin >> qt >> qs[i].u >> qs[i].v;
        qs[i].u--, qs[i].v--;
        qs[i].t = qt[0];
    }

    for (ll i = 0; i < k; i++) {
        qr cur = qs[k-i-1];
        if (cur.t == 'a') {
            qa[k-i-1] = 1 + (ldr(cur.u) == ldr(cur.v));
        } else {
            unite(cur.u, cur.v);
        }
    }

    for (ll i = 0; i < k; i++) {
        if (qa[i] == 1) {
            cout << "NO\n";
        }
        if (qa[i] == 2) {
            cout << "YES\n";
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
