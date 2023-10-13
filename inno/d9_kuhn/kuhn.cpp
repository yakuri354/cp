// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

vector<vector<ll>> g_a;
vector<ll> used_a;
vector<ll> mt_a, mt_b;

bool dfs(ll v, ll i) {
    if (used_a[v] == i) {
        return false;
    }
    used_a[v] = i;

    for (ll u : g_a[v]) {
        if (mt_b[u] == -1 || dfs(mt_b[u], i)) {
            mt_b[u] = v;
            mt_a[v] = u;
            return true;
        }
    }

    return false;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    g_a.resize(n);

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        while (x != 0) {
            g_a[i].push_back(x - 1);
            cin >> x;
        }
    }

    mt_a.assign(n, -1);
    mt_b.assign(m, -1);
    used_a.assign(n, -1);

    ll ans = 0;
    
    for (ll i = 0; i < n; i++) {
        ans += dfs(i, i);
    }
    
    cout << ans << '\n';

    for (ll i = 0; i < n; i++) {
        if (mt_a[i] != -1) {
            cout << i + 1 << ' ' << mt_a[i] + 1 << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
