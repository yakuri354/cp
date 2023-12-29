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

    bool operator<(const node &o) const {
        return make_tuple(v, sum, ix) < make_tuple(o.v, o.sum, o.ix);
    }
};

const node node_id = {inf, inf, inf};

vector<vector<node>> d;
vector<vector<ll>> a, parent;

void solve() {
    cin >> n >> m;

    a.resize(n, vector<ll>(m));
    // d_lo.resize(n, vector<node>(m));
    // d_hi.resize(n, vector<node>(m));
    // res_last.resize(m);

    // d_pref_lo.resize(n, vector<node>(m + 1));
    // d_suff_hi.resize(n, vector<node>(m + 1));

    d.resize(n, vector<node>(m));

    parent.resize(n, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
    }

    for (ll j = 0; j < m; j++) {
        d[0][j] = {0, j, a[0][j]};

        // d_lo[0][j] = {-a[0][j], j, a[0][j]};
        // d_hi[0][j] = {a[0][j], j, a[0][j]};
        parent[0][j] = -1;
    }

    for (ll i = 1; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            d[i][j] = node_id;

            for (ll k = 0; k < m; k++) {
                node res = {
                    d[i-1][k].v + abs(a[i][j] - a[i-1][k]),
                    j,
                    a[i][j] + d[i-1][k].sum
                };
                
                if (d[i][j].v == inf || res < d[i][j]) {
                    d[i][j] = res;
                    parent[i][j] = k;
                }
            }
        }
    }

    vector<ll> ans;

    ll curr = accumulate(d[n-1].begin(), d[n-1].end(), node_id).ix;
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
