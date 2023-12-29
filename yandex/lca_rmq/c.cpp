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

const ll maxn = 2e5;
const ll maxlg = 19;

ll n, timer = 0;

ll t[2 * maxn], tin[maxn], tout[maxn];

ll get_st(ll i) {
    ll res = t[i += n];
    while (i > 0) res += t[i /= 2];
    return res;
}

void add_st(ll l, ll r, ll x) {
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) t[l++] += x;
        if (r & 1) t[--r] += x;
    }
}

vector<pair<ll, ll>> g[maxn];

ll binup[maxlg][maxn];

map<ll, vector<ll>> len_edges;

void dfs1(ll v, ll p, ll lp) {
    tin[v] = timer++;
    binup[0][v] = p;
    for (ll i = 1; i < maxlg; i++) {
        binup[i][v] = binup[i-1][binup[i-1][v]];
    }
    if (lp != -1) {
        len_edges[lp].push_back(v);
    }
    for (auto [u, l]: g[v]) {
        if (u == p) continue;
        dfs1(u, v, l);
    }
    tout[v] = timer;
}

struct qr {
    ll a, b, x, i;
};

vector<qr> qs;

bool is_parent_or_same(ll a, ll b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

ll binup_lca(ll a, ll b) { // sus
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
        ll a, b, l;
        cin >> a >> b >> l;
        a--, b--;

        g[a].push_back({b, l});
        g[b].push_back({a, l});
    }

    dfs1(0, 0, -1);

    for (ll i = 0; i < q; i++) {
        ll a, b, x;
        cin >> a >> b >> x;
        a--, b--;

        qs[i] = {a, b, x, i};
    }

    sort(qs.begin(), qs.end(), [](qr a, qr b) {
        return a.x < b.x;
    });

    vector<ll> q_ans(q);

    ll max_l = 0;
    for (qr q: qs) {
        while (q.x > max_l) {
            max_l++;
            if (len_edges.count(max_l) == 0) continue;
            for (ll v: len_edges[max_l]) {
                add_st(tin[v], tout[v], 1);
            }
        }

        q_ans[q.i] = get_st(tin[q.a]) + get_st(tin[q.b]) - 2 * get_st(tin[binup_lca(q.a, q.b)]);
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

