// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 2e5;

struct edge {
    ll u, c, i;

    bool operator<(const edge& o) const {
        return c < o.c;
    }
};

unordered_map<ll, vector<ll>> g2;  // sus slow
vector<vector<edge>> out, inward;

const ll PREF_E = 1e7;
const ll SKUF_E = 1e14;

vector<ll> ans;
vector<ll> stack;
unordered_map<ll, ll> col;

bool find_cycle(ll v) {
    if (col[v] == 2)
        return false;
    if (col[v] == 1) {
        // cycle found

        auto pos = find(stack.begin(), stack.end(), v);

        ans.assign(stack.end() - pos, 0);
        copy(pos, stack.end(), ans.begin());
        return true;
    }

    col[v] = 1;
    stack.push_back(v);

    for (ll u : g2[v]) {
        if (find_cycle(u))
            return true;
    }

    col[v] = 2;
    stack.pop_back();

    return false;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    out.assign(n, {});
    inward.assign(n, {});
    ans.clear();
    stack.clear();
    col.clear();
    g2.clear();

    for (ll i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;

        out[u].push_back({v, c, i});
        inward[v].push_back({u, c, i});
    }

    for (ll i = 0; i < n; i++) {
        auto &o = out[i], &iw = inward[i];
        sort(o.begin(), o.end());

        for (ll j = 0; j < o.size(); j++) {
            g2[o[j].i + PREF_E].push_back(o[j].i);
            g2[o[j].i + SKUF_E].push_back(o[j].i);

            if (j < o.size() - 1) {
                g2[o[j].i + SKUF_E].push_back(o[j + 1].i + SKUF_E);
            }

            if (j > 0) {
                g2[o[j].i + PREF_E].push_back(o[j - 1].i + PREF_E);
            }
        }

        for (ll j = 0; j < iw.size(); j++) {
            ll lb = lower_bound(o.begin(), o.end(), edge{.c = iw[j].c}) - o.begin();
            ll ub = upper_bound(o.begin(), o.end(), edge{.c = iw[j].c}) - o.begin();

            if (lb > 0) {
                g2[iw[j].i].push_back(o[lb - 1].i + PREF_E);
            }

            if (ub < o.size()) {
                g2[iw[j].i].push_back(o[ub].i + SKUF_E);
            }
        }
    }

    for (ll i = 0; i < m; i++) {
        if (find_cycle(i)) {
            ll sz = 0;
            for (ll x : ans) {
                if (x <= m) sz++;
            }
            cout << sz << '\n';
            for (ll x : ans) {
                if (x <= m) cout << x + 1 << ' ';
            }
            cout << endl;
            return;
        }
    }

    cout << -1 << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
