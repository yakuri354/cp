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
using ull = unsigned long long;
using fl = long double;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> nxt(n), curr_out(n, (1ll << 50));
    iota(nxt.begin(), nxt.end(), 0);

    for (ll i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;

        if (c < curr_out[u]) {
            nxt[u] = v;
            curr_out[u] = c;
        }

        if (c < curr_out[v]) {
            nxt[v] = u;
            curr_out[v] = c;
        }
    }

    vector<ll> used, ans(n);
    for (ll i = 0; i < n; i++) {
        used.assign(n, -1);
        ll curr = i, len = 0;
        while (used[curr] == -1) {
            used[curr] = len;
            curr = nxt[curr];
            len++;
        }

        ll pos = k;
        if (pos > used[curr]) {
            pos = used[curr] + (k - used[curr]) % (len - used[curr]);
        }

        curr = i;
        for (ll j = 0; j < pos; j++) curr = nxt[curr];

        ans[i] = curr;
    }

    for (ll i = 0; i < n; i++) {
        cout << ans[i] + 1 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
