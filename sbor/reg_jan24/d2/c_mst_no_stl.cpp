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

const ll maxv = 1500001;
// const ll maxv = 100;
const ll maxn = 500000;
// const ll maxn = 100;

ll a[maxn], n, q, from[maxv];

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
        from[i] = i;
    }

    build();

    for (ll qi = 0; qi < q; qi++) {
        ll ty;
        cin >> ty;

        if (ty == 1) {
            ll x;
            cin >> x;
        
            from[x+1] = from[x];
        } else if (ty == 2) {
            ll l, r, y;
            cin >> l >> r >> y;
            l--;

            ll ans = query(l, r, from[y+1]);

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

