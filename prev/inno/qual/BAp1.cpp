// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 2e5 + 10;

vector<ll> g[maxn];
vector<tuple<ll, ll, ll>> g1[maxn];
ll s[maxn], p[maxn], tin[maxn], tout[maxn];
ll edge_child[maxn], edge_w[maxn];
ll head[maxn]; // «голова» тяжелого пути, которому принадлежит v
ll t = 0;

void sizes(ll v = 0) {
    s[v] = 1;
    for (ll &u : g[v]) {
        sizes(u);
        s[v] += s[u];
        if (s[u] > s[g[v][0]])
            // &u -- это ссылка, так что её легально использовать при swap-е
            swap(u, g[v][0]);
    }
}

void hld(ll v = 0) {
    tin[v] = t++;
    for (ll u : g[v]) {
        // если это тяжелый ребенок -- его next нужно передать
        // в противном случае он сам является головой нового пути
        head[u] = (u == g[v][0] ? head[v] : u);
        hld(u);
    }
    tout[v] = t;
}

ll n;  // array size
ll st[2 * maxn];

void build() {  // build the tree
  for (ll i = n - 1; i > 0; --i) st[i] = st[i<<1] + st[i<<1|1];
}

void modify(ll p, ll value) {  // set value at position p
  for (st[p += n] = value; p > 1; p >>= 1) st[p>>1] = st[p] + st[p^1];
}

ll query(ll l, ll r) {  // sum on ll [l, r)
  ll res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += st[l++];
    if (r&1) res += st[--r];
  }
  return res;
}

void upd(ll v, ll x) {
    modify(tin[v], x);
}

ll ancestor(ll a, ll b) {
    return tin[a] <= tin[b] && tin[b] < tout[a];
}

void up(ll &a, ll &b, ll &ans) {
    while (!ancestor(head[a], b)) {
        ans += query(tin[head[a]], tin[a] + 1);
        a = p[head[a]];
    }
}

ll sum(ll a, ll b) {
    ll ans = 0;
    up(a, b, ans);
    up(b, a, ans);
    if (!ancestor(a, b))
        swap(a, b);
    ans += query(tin[a] + 1, tin[b] + 1);
    return ans;
}

void dfs1(ll v, ll p1) {
    for (auto [u, i, w] : g1[v]) {
        if (u == p1) continue;

        p[u] = v;
        g[v].push_back(u);
        edge_child[i] = u;
        edge_w[u] = w;
        dfs1(u, v);
    }
}

void solve() {
    cin >> n;

    vector<ll> weights(n);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;

        weights[i] = w;

        g1[u-1].emplace_back(v-1, i, w);
        g1[v-1].emplace_back(u-1, i, w);
    }

    dfs1(0, -1);

    sizes();
    hld();

    for (ll i = 0; i < n - 1; i++) {
        upd(edge_child[i], weights[i]);
    }

    ll q;
    cin >> q;
    while (q--) {
        ll qt;
        cin >> qt;
        if (qt == 1) {
            ll i, w;
            cin >> i >> w;
            i--;

            upd(edge_child[i], w);
        } else if (qt == 2) {
            ll u, v;
            cin >> u >> v;
            u--, v--;

            cout << sum(u, v) << '\n';
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
