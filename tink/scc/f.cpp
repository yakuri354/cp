// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

vector<vector<ll>> adj;
vector<ll> cost;
vector<ll> ord;
vector<bool> used;

void dfs(ll v) {
    used[v] = true;
    for (ll u : adj[v]) {
        if (!used[u])
            dfs(u);
    }
    ord.push_back(v);
}

void solve() {
    ll n;
    cin >> n;
    cost.resize(n);
    adj.resize(n);
    used.resize(n);

    for (ll i = 0; i < n; i++) {
        cin >> cost[i];
    }

    for (ll i = 0; i < n; i++) {
        ll k;
        cin >> k;
        for (ll j = 0; j < k; j++) {
            ll a;
            cin >> a;
            a--;

            adj[i].push_back(a);
        }
    }

    dfs(0);
    // reverse(ord.begin(), ord.end());
    ll sum = 0;
    for (ll i : ord) {
        sum += cost[i];
    }
    cout << sum << ' ' << ord.size() << endl;
    for (ll v : ord) {
        cout << v + 1 << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
