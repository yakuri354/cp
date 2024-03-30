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
#include <optional>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

set<pll> el; // todo slow
vector<ll> stack;
vector<bool> used;
ll dl, dr;

ll dfs(ll v, bool white, ll p) {
    if (used[v]) {
        stack.push_back(v);
        return v;
    }
    used[v] = true;
    for (ll u = dl; u < dr; u++) {
        if (u != p && u != v && el.count({min(u, v), max(u, v)}) == white) {
            ll k = dfs(u, white, v);
            if (k == -2) return -2;
            if (k >= 0) {
                if (k == v) return -2;
                stack.push_back(v);
                return k;
            }
        }
    }
    return -1;
}

optional<vector<ll>> findcyc(ll l, ll r) {
    dl = l, dr = r;
    stack.clear();
    for (ll i = l; i < r; i++) {
        used[i] = false;
    }
    for (ll i = l; i < r; i++) {
        if (!used[i]) {
            if (dfs(i, true, -1) != -1) {
                return stack;
            }
        }
    }
    stack.clear();
    for (ll i = l; i < r; i++) {
        used[i] = false;
    }
    for (ll i = l; i < r; i++) {
        if (!used[i]) {
            if (dfs(i, false, -1) != -1) {
                return stack;
            }
        }
    }
    for (ll i = l; i < r; i++) {
        used[i] = false;
    }
    return {};
}

void solve() {
    ll n, m;
    cin >> n >> m;

    used.resize(n);
    
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        el.insert({min(a, b), max(a, b)});
    }

    // vector<vector<ll>> scs(n);

    // for (ll i = 0; i + 5 <= n; i++) { // opt
    //     auto res = findcyc(i, min(n, i + 5));
    //     if (!res.has_value() || res->size() > 5) exit(-1);

    //     scs[i] = std::move(*res);
    // }

    ll q;
    cin >> q;
    
    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;

        if (r - l <= 2) {
            cout << -1 << '\n';
            continue;
        }

        auto res = findcyc(l, min(r, l + 6));
        if (res.has_value()) {
            cout << res->size() << ' ';
            for (ll i : *res) cout << i + 1 << ' ';
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }

        // if (r - l >= 5) {
        //     cout << scs[l].size() << ' ';
        //     for (ll i : scs[l]) cout << i + 1 << ' ';
        //     cout << '\n';
        // } else {
        //     auto res = findcyc(l, r);
        //     if (res.has_value()) {
        //         cout << res->size() << ' ';
        //         for (ll i : *res) cout << i + 1 << ' ';
        //         cout << '\n';
        //     } else {
        //         cout << -1 << '\n';
        //     }
        // }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

