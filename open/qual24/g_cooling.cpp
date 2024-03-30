// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <sys/signal.h>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = __int128;
using l1 = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 2e5;

ll n, one, all;
ll h[maxn];

bool check(ll m) {
    if (one >= all) {
        ll delta = one - all;

        if (delta == 0) {
            for (ll i = 0; i < n; i++) {
                if (h[i] - all * m >= 0) return false;
            }
            return true;
        }

        ll cnt_delta = 0;
        for (ll i = 0; i < n; i++) {
            ll diff = max(h[i] - all * m + 1, ll(0));
            cnt_delta += diff / delta + (diff % delta != 0);
        }

        return cnt_delta <= m;
    } else {
        ll delta = all - one;

        ll cnt_delta = 0;
        for (ll i = 0; i < n; i++) {
            if (h[i] - all * m >= 0) return 0;
            cnt_delta += (all * m - h[i] - 1) / delta; // sus
        }

        return cnt_delta >= m;
    }
}

void solve() {
    l1 _n, _one, _all;
    cin >> _n >> _one >> _all;
    n = _n, one = _one, all = _all;

    bool easy = true;
    for (ll i = 0; i < n; i++) {
        l1 x;
        cin >> x;
        h[i] = x;
        easy &= h[i] < 0;
    }

    if (easy) {
        cout << 0 << endl;
        return;
    }

    ll lo = 0, hi = 1e12;
    while (hi - lo > 1) {
        ll m = (hi + lo) / 2;

        if (check(m)) hi = m;
        else lo = m;
    }

    cout << ull(hi) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

