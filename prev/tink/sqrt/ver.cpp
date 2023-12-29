// #pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
#include <unordered_map>

#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
const ll bs = 500;

ll col[maxn];
vector<ll> adj[maxn];
vector<ll> hvadj[maxn];
unordered_map<ll, unordered_map<ll, ll>> conn;

template <typename T>
void aori(T &m, ll k, ll x) {
    if (m.count(k))
        m[k] += x;
    else
        m[k] = x;
}

bool heavy(ll v) {
    return adj[v].size() >= bs;
}

ll n, m, q, status = 0;

void solve() {
    cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        cin >> col[i];
    }

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (ll i = 0; i < n; i++) {
        if (heavy(i)) {
            conn[i] = {};
        }

        for (ll v : adj[i]) {
            if (col[i] != col[v]) status++;
            if (heavy(i)) {
                aori(conn[i], col[v], 1);
            }
            if (heavy(v)) {
                hvadj[i].push_back(v);
            }
        }
    }

    status >>= 1;

    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll v, x;
        cin >> v >> x;
        v--;

        if (x == col[v]) {
            cout << status << endl;
            continue;
        }

        for (ll u : hvadj[v]) { // sqrt n
            conn[u][col[v]]--;
            aori(conn[u], x, 1);
        }

        if (heavy(v)) {
            if (conn[v].count(col[v]))
                status += conn[v][col[v]];
            if (conn[v].count(x))
                status -= conn[v][x];
        } else {
            for (ll u : adj[v]) { // sqrt n
                if (col[u] == col[v]) status++;
                if (col[u] == x) status--;
            }
        }

        col[v] = x;

        cout << status << endl;
    }
}
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
