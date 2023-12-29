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

const ll maxnm = 1e5;
const ll inf = 1ll << 40;

ll n, m;

struct node {
    ll v, ix, sum;

    node operator+(const node &o) const {
        if (make_tuple(v, sum, ix) < make_tuple(o.v, o.sum, o.ix)) {
            return *this;
        } else {
            return o;
        }
    }
};

const node node_id = {inf, inf, inf};

struct segt {
    vector<node> t;
    vector<node> a;

    ll size;

    segt(ll size): t(size * 2), a(size) {

    }
    
    void build() {
        for (ll i = size - 1; i > 0; i++) {
            t[i] = t[i*2] + t[i*2+1];
        }
    }

    node query(ll l, ll r) {
        node res = node_id;
        for (l += size, l += size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = res + t[l++];
            if (r & 1) res = res + t[--r];
        }
        return res;
    }

};

vector<vector<ll>> a;
vector<vector<node>> d_lo, d_hi, d_pref_lo, d_suff_hi;

vector<node> res_last;

vector<vector<ll>> parent;

void calc_pref(ll i) {
    d_pref_lo[i][0] = node_id;
    for (ll j = 1; j <= m; j++) {
        d_pref_lo[i][j] = d_lo[i][j-1] + d_pref_lo[i][j-1];
    }

    d_suff_hi[i][m] = node_id;
    for (ll j = m - 1; j >= 0; j--) {
        d_suff_hi[i][j] = d_hi[i][j] + d_suff_hi[i][j+1];
    }
}

void solve() {
    cin >> n >> m;

    a.resize(n, vector<ll>(m));
    d_lo.resize(n, vector<node>(m));
    d_hi.resize(n, vector<node>(m));
    res_last.resize(m);

    d_pref_lo.resize(n, vector<node>(m + 1));
    d_suff_hi.resize(n, vector<node>(m + 1));

    parent.resize(n, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
    }

    for (ll j = 0; j < m; j++) {
        // d[0][j] = 0
        d_lo[0][j] = {-a[0][j], j, a[0][j]};
        d_hi[0][j] = {a[0][j], j, a[0][j]};
        parent[0][j] = -1;
    }

    calc_pref(0);

    for (ll i = 1; i < n; i++) {
        ll k = 0;
        for (ll j = 0; j < m; j++) {
            while (k < m && a[i-1][k] < a[i][j]) k++;

            auto r_lo = d_pref_lo[i-1][k], r_hi = d_suff_hi[i-1][k];

            r_lo.v += a[i][j];
            r_hi.v -= a[i][j];

            auto res = r_lo + r_hi;

            if (i == n - 1) {
                res_last[j] = res;
                res_last[j].ix = j;
            }
        
            d_lo[i][j] = {res.v - a[i][j], j, res.sum + a[i][j]};
            d_hi[i][j] = {res.v + a[i][j], j, res.sum + a[i][j]};

            parent[i][j] = res.ix;
        }
        calc_pref(i);
    }

    vector<ll> ans;

    ll curr = accumulate(res_last.begin(), res_last.end(), node_id).ix;
    for (ll i = n - 1; i > 0; i--) {
        ans.push_back(a[i][curr]);
        curr = parent[i][curr];
    }

    ans.push_back(a[0][curr]);

    sort(ans.begin(), ans.end());

    for (ll i: ans) {
        cout << i << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
