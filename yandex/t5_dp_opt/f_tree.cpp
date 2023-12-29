// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
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

const ll inf = 1ll << 60;

struct line {
    ll k, b;

    ll operator()(ll x) {
        return k * x + b;
    }
};

struct lichao {
    unordered_map<ll, line> t;

    const static ll L = -inf, R = inf;

    void add(line f) {
        return _add(0, L, R, f);
    }

    ll get_min(ll x) {
        return _min(0, L, R, x);
    }

    void extend(lichao& o) {
        auto dfs = [&](ll i, auto self) -> void {
            if (o.t.count(i) == 0) return;

            add(o.t[i]);

            self(i * 2 + 1, self);
            self(i * 2 + 2, self);
        };

        dfs(0, dfs);
    }

   private:
    void _add(ll i, ll l, ll r, line f) {
        if (!t.count(i)) {
            t[i] = f;
            return;
        }

        ll m = (l + r) / 2;

        bool lb = f(l) < t[i](l), mb = f(m) < t[i](m);

        if (mb) swap(f, t[i]);

        if (r - l < 2) return;

        if (lb != mb) {  // left
            _add(i * 2 + 1, l, m, f);
        } else {
            _add(i * 2 + 2, m, r, f);
        }
    }

    ll _min(ll i, ll l, ll r, ll x) {
        if (t.count(i) == 0) {
            return inf;
        }

        ll m = (l + r) / 2;

        if (r - l < 2) return t[i](x);

        if (x < m) {
            return min(t[i](x), _min(i * 2 + 1, l, m, x));
        } else {
            return min(t[i](x), _min(i * 2 + 2, m, r, x));
        }
    }
};

vector<vector<ll>> g;
vector<ll> a, b, d;

ll ans = 0;

unique_ptr<lichao> dfs(ll v, ll p) {
    vector<unique_ptr<lichao>> ch;
    for (ll u : g[v]) {
        if (u == p)
            continue;

        ch.push_back(dfs(u, v));
    }

    if (ch.empty()) {
        auto t = make_unique<lichao>();

        t->add({b[v], 0});
        d[v] = 0;

        return t;
    }

    ll mi = max_element(ch.begin(), ch.end(), [](auto &a, auto &b) {
        return a->t.size() < b->t.size();
    }) - ch.begin();

    for (ll i = 0; i < ch.size(); i++) {
        if (i == mi)
            continue;

        ch[mi]->extend(*ch[i]);
        ch[i] = {};
    }

    d[v] = ch[mi]->get_min(a[v]);
    
    ch[mi]->add({b[v], d[v]});

    return std::move(ch[mi]);
}

void solve() {
    ll n;
    cin >> n;
    
    a.resize(n);
    b.resize(n);
    d.resize(n);

    g.resize(n);

    for (ll& i : a)
        cin >> i;
    for (ll& i : b)
        cin >> i;

    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, -1);

    for (ll i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
