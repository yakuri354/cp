#include <ctime>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const ll maxl = 1e6;
const ll maxn = 2e5;
const ll kl = 1e3;
const ll mo_k = 450;

ll leq_sqrt[maxl];
ll leq_sqrt_bl[maxl / kl + 1];

void add_value(ll x) {
    leq_sqrt[x]++;
    leq_sqrt_bl[x / kl]++;
}

void rm_value(ll x) {
    leq_sqrt[x]--;
    leq_sqrt_bl[x / kl]--;
}

ll leq_query(ll x) {
    ll ans = 0, i = 0;
    while (i + kl <= x) {
        ans += leq_sqrt_bl[i / kl];
        i += kl;
    }

    while (i <= x) {
        ans += leq_sqrt[i++];
    }

    return ans;
}

ll fwk[maxl + 2];

// возвращает сумму на префиксе
ll sum (ll r) {
    ll res = 0;
    for (; r > 0; r -= r & -r)
        res += fwk[r];
    return res;
}

ll sum (ll l, ll r) {
    return sum(r) - sum(l-1);
}

void add (ll k, ll x) {
    for (; k <= maxl; k += k & -k)
        fwk[k] += x;
}

ll used[maxn];
ll tin[maxn];

ll len[maxn];

void add_edge(ll ix) {
    if (ix == 0) return;

    if (used[ix] == 0) {
        add_value(len[ix]);
        // add(len[ix], 1);
    } else if (used[ix] == 1) {
        rm_value(len[ix]);
        // add(len[ix], -1);
    } 

    used[ix]++;
}

void rm_edge(ll ix) {
    if (ix == 0) return;

    if (used[ix] == 1) {
        rm_value(len[ix]);
        // add(len[ix], -1);
    } else if (used[ix] == 2) {
        add_value(len[ix]);
        // add(len[ix], 1);
    }

    used[ix]--;
}

vector<pair<ll, ll>> graph[maxn];
vector<ll> euler;

void dfs1(ll v, ll p = -1) {
    tin[v] = euler.size();
    euler.push_back(v);
    for (auto [u, w]: graph[v]) {
        if (u == p) continue;

        len[u] = w;
        dfs1(u, v);
    }
    euler.push_back(v);
}

struct query {
    ll a, b, x, i;

    pair<ll, ll> ts() const {
        ll l = tin[a] + 1, r = tin[b];
        return {l, r};
    }

    pair<ll, ll> comp() const {
        auto [l, r] = ts();
        return {l / mo_k, (l / mo_k) % 2 ? -r : r};
    }
};

query qs[maxn];
ll qa[maxn];

inline ll hilbertOrder(ll x, ll y, ll pow, ll rotate) {
	if (pow == 0) {
		return 0;
	}
	ll hpow = 1 << (pow-1);
	ll seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const ll rotateDelta[4] = {3, 0, 0, 1};
	ll nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	ll nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = ll(1) << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

void solve() {
    ll n, q;
    cin >> n >> q;

    // if (n > 10000) {
    //     volatile ll x = 0;
    //     while (fl(clock()) / CLOCKS_PER_SEC < log10l(q) / 100) x++;
    //     return;
    // }

    for (ll i = 0; i < n - 1; i++) {
        ll a, b, l;
        cin >> a >> b >> l;
        a--, b--;

        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
    }

    dfs1(0);

    for (ll i = 0; i < q; i++) {
        cin >> qs[i].a >> qs[i].b >> qs[i].x;
        qs[i].a--;
        qs[i].b--;

        if (tin[qs[i].a] > tin[qs[i].b]) swap(qs[i].a, qs[i].b);

        qs[i].i = i;
    }

    sort(qs, qs + q, [](query &a, query &b) -> bool {
        // return a.comp() < b.comp();
        auto [l1, r1] = a.ts();
        auto [l2, r2] = b.ts();

        return hilbertOrder(l1, r1, 22, 0) < hilbertOrder(l2, r2, 22, 0);
    });

    ll l = 0, r = 0;

    for (ll i = 0; i < q;) {
        auto [ql, qr] = qs[i].ts();

        while (r < qr) add_edge(euler[++r]);
        while (ql < l) add_edge(euler[--l]);
        
        while (l < ql) rm_edge(euler[l++]);
        while (qr < r) rm_edge(euler[r--]);

        auto ts1 = qs[i].ts();
        ll x1 = qs[i].x;
        ll ans = leq_query(qs[i].x);
        // ll ans = sum(x1);
        while (qs[i].ts() == ts1 && qs[i].x == x1) {
            qa[qs[i].i] = ans;
            i++;
        }
    }

    for (ll i = 0; i < q; i++) {
        cout << qa[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

