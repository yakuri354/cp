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
using pll = pair<ll, ll>;

using graph = vector<vector<ll>>;

graph g;

ll n, m;

ll mod(ll x) {
    return x % ll(998244353);
}

ll binexp(ll b, ll p) {
    if (p == 0) return 1;

    if (p % 2 == 0) {
        ll x = binexp(b, p / 2);
        return mod(x * x);
    } else {
        return mod(b * binexp(b, p - 1));
    }
}

bool is_bamboo() {
    ll c1 = 0, c2 = 0;

    for (ll i = 0; i < n; i++) {
        if (g[i].size() == 1) c1++;
        if (g[i].size() == 2) c2++;
    }

    return c1 == 2 && c2 + c1 == n;
}

void solve_bamboo() {
    cout << binexp(2, max(n - 2, 0ll)) << '\n';
}

void solve() {
    cin >> n >> m;

    g.assign(n, {});

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    // if (is_bamboo()) {
        solve_bamboo();
    // } else {
        // cout << 0 << '\n';
    // }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t --> 0)
        solve();
}
