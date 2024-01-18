// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1e5;
const ll maxlg = 17;

const ll inf0 = 1ll << 33;

ll n, timer = 0;

ll t[2 * maxn], tin[maxn], tout[maxn];

ll st_get(ll i) {
    ll res = t[i += n];
    while (i > 0) res += t[i /= 2];
    return res;
}

void st_add(ll l, ll r, ll x) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) t[l++] += x;
        if (r & 1) t[--r] += x;
    }
}

struct edge {
    ll u, c, d;
};

vector<edge> g[maxn];

ll binup[maxlg][maxn];
vector<vector<edge>> v_by_color;

void dfs1(ll v, ll p, ll depth) {
    tin[v] = timer++;
    t[n + tin[v]] = depth;
    binup[0][v] = p;
    for (ll i = 1; i < maxlg; i++) {
        binup[i][v] = binup[i-1][binup[i-1][v]];
    }
    for (auto [u, c, d]: g[v]) {
        if (u == p) continue;
        
        v_by_color[c].push_back({u, c, d});
        dfs1(u, v, depth + d);
    }
    tout[v] = timer;
}

struct qr {
    ll a, b, c, d, i;
};

vector<qr> qs;

bool is_parent_or_same(ll a, ll b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

ll binup_lca(ll a, ll b) {
    if (is_parent_or_same(a, b)) return a;

    for (ll i = maxlg - 1; i >= 0; i--) {
        if (!is_parent_or_same(binup[i][a], b)) {
            a = binup[i][a];
        }
    }

    return binup[0][a];
}

void solve() {
    ll q;
    cin >> n >> q;

    qs.resize(q);

    for (ll i = 0; i < n - 1; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--;

        g[a].push_back({b, c, d});
        g[b].push_back({a, c, d});
    }

    v_by_color.resize(n + 1);

    dfs1(0, 0, 0);

    for (ll i = 0; i < q; i++) {
        ll a, b, c, d;
        cin >> c >> d >> a >> b;
        a--, b--;

        qs[i] = {a, b, c, d, i};
    }

    sort(qs.begin(), qs.end(), [](qr a, qr b) {
        return a.c < b.c;
    });

    vector<ll> q_ans(q);

    ll curr_col = -1;
    for (qr q: qs) {
        if (curr_col != q.c) {
            if (curr_col != -1) {
                for (auto [u, c, d]: v_by_color[curr_col]) {
                    st_add(tin[u], tout[u], -inf0 + d);
                }
            }

            for (auto [u, c, d]: v_by_color[q.c]) {
                st_add(tin[u], tout[u], inf0 - d);
            }

            curr_col = q.c;
        }

        ll res1 = st_get(tin[q.a]) + st_get(tin[q.b]) - 2 * st_get(tin[binup_lca(q.a, q.b)]);

        q_ans[q.i] = res1 % inf0 + (res1 / inf0) * q.d;
    }

    for (ll i = 0; i < q; i++) {
        cout << q_ans[i] << '\n';
    }

    cout << flush;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


