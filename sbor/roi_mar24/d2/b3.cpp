#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <array>
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
using pll = pair<ll, ll>;

ll k, n, m, q;

const ll maxv = 50000ll * 5;
const ll maxk = 5;
const ll inf = 1e11 - 1;
const ll sq = 100;

vector<pll> g[maxv];

// ll dp[maxv]; // todo optimize

struct kalmass {
    const ll delta = inf + 1;

    vector<ll> a;
    ll state = delta;

    kalmass(ll n): a(n, delta) {}

    bool has(ll v) const {
        return a[v] >= state;
    }

    ll get(ll i) const {
        if (has(i)) {
            return a[i] - state;
        } else {
            return delta - 1;
        }
    }

    void set(ll i, ll x) {
        x = min(x, delta - 1);
        a[i] = x + state;
    }

    void remove(ll i) {
        a[i] = 0;
    }

    ll operator[](ll i) const {
        return get(i);
    }

    void clear() {
        state += delta;
    }
};

kalmass dp0(maxv + 100);

ll dfs_dist(ll v, ll to) {
    if (v > to + k) return inf;
    if (v == to) return 0;
    if (dp0.has(v)) return dp0[v];

    dp0.set(v, inf);

    for (auto [u, w]: g[v]) {
        dp0.set(v, min(ll(dp0[v]), dfs_dist(u, to) + w));
    }

    return dp0.get(v);
}

ll next_bl[maxv][maxk];

void answer(ll a) {
    if (a >= inf) {
        cout << "-1\n";
    } else {
        cout << a << '\n';
    }
}

void solve() {
    cin >> k >> n >> m >> q;

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
    
        g[a].push_back({b, c});
    }

    for (ll i = sq * k; i + k <= n; i += sq * k) {
        ll prev = i - sq * k;

        for (ll z = 0; z < k; z++) {
            dp0.clear();

            for (ll j = 0; j < k; j++) {
                next_bl[prev + j][z] = dfs_dist(prev + j, i + z);
            }
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll u, v;
        cin >> u >> v;

        if (v < u || v / k == u / k) {
            answer(inf);
            continue;
        }

        if (v / (k * sq) == u / (k * sq)) {
            dp0.clear();
            answer(dfs_dist(u, v));
            continue;
        }

        ll nx = (u / (k * sq) + 1) * k * sq;

        array<ll, maxk> dist0{};

        for (ll i = 0; i < k; i++) {
            dp0.clear();
            dist0[i] = dfs_dist(u, nx + i);
        }

        while (nx + (k * sq) < v) {
            array<ll, maxk> dist1;
            dist1.fill(inf);
            for (ll i = 0; i < k; i++) {
                for (ll j = 0; j < k; j++) {
                    dist1[i] = min(ll(dist1[i]), dist0[j] + next_bl[nx + j][i]);
                }
            }
            dist0 = dist1;
            nx += k * sq;
        }

        ll ans = inf;
        dp0.clear();
        for (ll i = 0; i < k; i++) {
            ans = min(ans, dist0[i] + dfs_dist(nx + i, v));
        }

        answer(ans);
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

