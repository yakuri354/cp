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
using ll = int;
using ull = unsigned int;
using fl = long double;

struct node {
    vector<int> ixs;
    ll val;
};

const ll maxv = 1500001;
// const ll maxv = 100;
const ll maxn = 500000;
// const ll maxn = 100;

node* n_now[maxv], *n_here[maxv];
node na[maxv];

ll a[maxn], n, q;

vector<int> t[maxn * 2];

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i].resize(t[i*2].size() + t[i*2+1].size());
        merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(), t[i].begin());
    }
}

ll lower_than(vector<int> &v, ll x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
}

ll query(ll l, ll r, ll x) {
    ll res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l & 1) res += lower_than(t[l++], x);
        if (r & 1) res += lower_than(t[--r], x);
    }
    return res;
}

void solve() {
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        t[i + n].push_back(a[i]);
    }

    for (ll i = 0; i < maxv; i++) {
        na[i].val = i;
        na[i].ixs.push_back(i);
        n_now[i] = na + i;
        n_here[i] = na + i;
    }

    build();

    for (ll qi = 0; qi < q; qi++) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll x;
            cin >> x;

            if (n_now[x]->ixs.size() == 0) continue;

            auto from_n = n_here[x];
            auto to_n = n_here[x + 1];

            if (to_n->ixs.size() < from_n->ixs.size()) {
                swap(n_here[x], n_here[x+1]);
                swap(from_n, to_n);
                n_here[x]->val = x;
                n_here[x+1]->val = x + 1;
            }

            for (ll i: from_n->ixs) {
                n_now[i] = to_n;
                // to_n->ixs.push_back(i);
            }

            ll from_sz = from_n->ixs.size(), to_sz = to_n->ixs.size();
            to_n->ixs.resize(from_sz + to_sz, 0);
            copy(from_n->ixs.begin(), from_n->ixs.end(), to_n->ixs.begin() + to_sz);

            from_n->ixs.clear();
        } else if (ty == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;

            ll lo = 0, hi = y + 1; // sus
            while (hi - lo > 1) {
                ll m = (lo + hi) / 2;

                if (n_now[m]->val > y) {
                    hi = m;
                } else {
                    lo = m;
                }
            }

            ll ans = query(l, r, hi);

            cout << ans << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

