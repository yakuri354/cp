// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ull = unsigned long long;
using fl = long double;

vector<vector<ll>> g, from, to;
vector<ll> a, di, ans, par;

// ll timer = 0;

const ll maxa = 1e6;
// const ll lgn = 20;

// void dfs(ll v, ll p) {
//     b2[v][0] = a[v];
//     b1[v][0] = p;
//     for (ll i = 1; i < lgn; i++) {
//         b1[v][i] = b1[b1[v][i-1]][i-1];
//         b2[v][i] = b2[v][i-1] + b2[b1[v][i-1]][i-1];
//     }

//     for (ll u: g[v]) {
//         dfs(u, v);
//     }
// }

void dfs(ll v, ll s) {
    s += a[v];
    for (ll i : from[v]) {
        ans[i] -= s;
    }

    for (ll i: to[v]) {
        ans[i] += s;
    }

    for (ll u: g[v]) {
        dfs(u, s);
    }
}

ll divcount(ll x) {
    ll res = 0;
    while (x != 1) {
        x /= di[x];
        res++;
    }
    return res;
}

void solve() {
    ll n, q;
    cin >> n >> q;

    g.resize(n);
    a.resize(n);
    from.resize(n);
    to.resize(n);
    par.resize(n);
    ans.resize(q);

    for (ll i = 1; i < n; i++) {
        ll p;
        cin >> p;
        g[p - 1].push_back(i);
        par[i] = p - 1;
    }

    di.resize(maxa + 1, 1);

    for (ll i = 2; i <= maxa; i++) {
        if (di[i] != 1) continue;
        for (ll j = i; j <= maxa; j += i) {
            if (di[j] == 1) {
                di[j] = i;
            }
        }
    }

    for (ll &i: a) {
        ll x;
        cin >> x;

        i = divcount(x);
    }

    for (ll i = 0; i < q; i++) {
        ll v, u;
        cin >> v >> u;

        u--, v--;

        if (v != 0) from[par[v]].push_back(i);
        to[u].push_back(i);
    }

    dfs(0, 0);

    for (ll i = 0; i < q; i++) {
        if (ans[i] % 2 == 1) {
            cout << "9\n";
        } else {
            cout << "36\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
