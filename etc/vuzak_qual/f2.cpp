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

    vector<ll> to_cycle(n, -1), cyc_len(n, -1);

    vector<ll> used, ans(n);
    for (ll i = 0; i < n; i++) {
        if (to_cycle[i] != -1) continue;

        used.assign(n, -1);
        ll curr = i, len = 0;
        while (used[curr] == -1) {
            used[curr] = len;
            curr = nxt[curr];
            len++;
        }

        ll c2 = i;
        for (ll pos = 0; pos <= used[curr]; pos++) {
            to_cycle[c2] = used[curr] - pos;
            cyc_len[c2] = len - used[curr];
            c2 = nxt[c2];
        }

        cyc_len[curr] = len - used[curr];
        to_cycle[curr] = 0;
        ll c3 = nxt[curr];
        while (c3 != curr) {
            cyc_len[c3] = len - used[curr];
            to_cycle[c3] = 0;
            c3 = nxt[c3];
        }
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
