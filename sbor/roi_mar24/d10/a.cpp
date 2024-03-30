#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <queue>
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
using pll = pair<ll, ll>;

const ll maxn = 5e5 + 1;

const ll tries = 3;
const ll all_tries = 30;

ll n;

vector<ll> t[maxn * 2];

void build() {
    for (ll i = n - 1; i > 0; i--) {
        t[i].resize(t[i*2].size() + t[i*2+1].size());
        merge(t[i*2].begin(), t[i*2].end(), t[i*2+1].begin(), t[i*2+1].end(), t[i].begin());
    }
}

ll between(vector<ll> &s, ll lo, ll hi) {
    return upper_bound(s.begin(), s.end(), hi) - lower_bound(s.begin(), s.end(), lo);
}

ll query(ll l, ll r, ll lo, ll hi) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += between(t[l++], lo, hi);
        if (r & 1) res += between(t[--r], lo, hi);
    }
    return res;
}

void solve() {
    ll q;
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        t[n + i] = {x};
    }

    build();

    mt19937_64 mt(0xab0ba);

    unordered_map<ll, ll> t1;

    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;

        t1.clear();
        priority_queue<pll, vector<pll>> t2;

        for (ll j = 0; j < all_tries; j++) {
            ll x = t[n + uniform_int_distribution<ll>(l, r - 1)(mt)][0];
            t1[x]++;
        }

        for (auto [k, v]: t1) {
            t2.push({v, k});
        }

        for (ll j = 0; j < tries && !t2.empty(); j++) {
            ll x = t2.top().second;
            t2.pop();
            if (query(l, r, x, x) > (r - l) / 2) {
                cout << x << '\n';
                goto nxt;
            }
        }

        cout << "0\n";
        nxt:;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
