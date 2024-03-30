#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
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
using pll = pair<ll, ll>;

bool dec(ll i, ll x) {
    cout << "- " << i + 1 << ' ' << x << endl;
    string s;
    cin >> s;

    if (s == "-1") exit(-1);

    return s == "OK";
}

ll geq_than(ll i) {
    cout << "? " << i + 1 << endl;
    ll x;
    cin >> x;
    if (x == -1) exit(-1);
    return x;
}

ll find_num(ll i, ll lo, ll hi) {
    // ll res;
    // cout << "num " << i + 1 << " is in [" << lo << "; " << hi << ") --> " << flush;
    // cin >> res;
    // return res;

    ll found = 0;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (dec(i, m - found)) {
            found = m;
            lo = m;
        } else {
            hi = m;
        }
    }

    return max(lo, found);
}

vector<ll> ans;
vector<pll> ueq;

void dnq(ll l, ll r, ll lo, ll hi) {
    if (r - l <= 0) return;

    if (hi - lo == 1) {
        for (ll i = l; i < r; i++) {
            ans[ueq[i].second] = lo;
        }
        return;
    } else if (r - l == 1) {
        ans[ueq[l].second] = find_num(ueq[l].second, lo, hi);
        return;
    }

    ll m = (l + r) / 2;
    ll v = find_num(ueq[m].second, lo, hi);
    ans[ueq[m].second] = v;
    
    dnq(l, m, lo, v + 1);
    dnq(m + 1, r, v, hi);
}

ll n, h, q;

void solve() {
    ans.assign(n, 0);
    ueq.assign(n, {});

    for (ll i = 0; i < n; i++) {
        ueq[i] = {geq_than(i), i};
    }

    sort(ueq.begin(), ueq.end(), greater<>());

    dnq(0, n, 0, h + 1);

    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        sum += ans[i];
    }

    cout << "! " << sum << endl;
    string s;
    cin >> s;
    if (s == "-1") exit(-1);
}

int main() {
    // cin.tie(nullptr);
    // ios::sync_with_stdio(false);
    ll t;
    cin >> t;
    cin >> n >> h >> q;
    for (ll i = 0; i < t; i++)
        solve();
}
