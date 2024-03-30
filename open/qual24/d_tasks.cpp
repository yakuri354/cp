// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <map>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

ll n, t, s;

vector<ll> a;

ll rnk(ll x) {
    ll v = max(t - x, 0ll);

    if (v % s == 0) return v / s;
    else return v / s + 1;
}

void solve() {
    cin >> n >> t >> s;

    a.resize(n);
    for (ll &i: a) cin >> i;

    reverse(a.begin(), a.end());

    // while (t > a.front()) t -= s; // sus

    unordered_map<ll, ll> idx, f_r, from_up;
    map<ll, ll> l_r;

    for (ll i = 0; i < n; i++) {
        idx[a[i]] = i;
        l_r[rnk(a[i])] = i;
    }

    for (ll i = n - 1; i >= 0; i--) {
        f_r[rnk(a[i])] = i;
    }

    ll curr = 0;
    ll cr = 0;
    for (ll i = 0; i < n; i++) {
        if (rnk(a[i]) != cr) {
            curr = max(curr + cr - rnk(a[i]), 0ll);
            cr = rnk(a[i]);
            from_up[rnk(a[i])] = curr;
        }
        curr++;
    }

    ll q;
    cin >> q;

    for (ll qi = 0; qi < q; qi++) {
        ll val, ord;
        cin >> val >> ord;

        ord--;

        ll ix = idx[val], r = rnk(val);

        ll downs = from_up[r] + (ix - f_r[r]);
        ll last_rank = r + downs;
        ll less_next = upper_bound(a.begin(), a.end(), last_rank, [](ll a, ll b) {
            return a < rnk(b);
        }) - a.begin() - ix - 1;
        ll lb = max(f_r[r] - from_up[r], 0ll);
        ll ub = ix + less_next;

        if (lb <= ord && ord <= ub) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

