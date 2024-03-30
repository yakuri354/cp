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
using pll = pair<ll, ll>;

const ll inf = 1e17;

struct box {
    ll w, c;
};

struct lis_state {
    ll n, l = 0;
    vector<ll> d;

    lis_state(ll n): n(n), d(n, inf) {
        d[0] = -inf;
    }
    
    void add(box x) {
        ll p = upper_bound(d.begin(), d.begin() + l, x.c) - d.begin() - 1;
        d[p] ;
        if (p > l) l++;
    }
};

void solve() {
    ll n;
    cin >> n;

    vector<box> a(n);
    for (auto &i: a) cin >> i.w >> i.c;

    sort(a.begin(), a.end(), [](box a, box b) {
        return a.c < b.c;
    });
    
    ll ans = 0;
    mt19937_64 mt(0xab0ba);
    for (ll it = 0; it < 10000; it++) {
        shuffle(a.begin(), a.end(), mt);
        vector<ll> d(n + 1, inf);
        d[0] = 0;

        for (ll i = 0; i < n; i++) {
            auto d2 = d;
            for (ll j = 0; j < n; j++) {
                if (d[j] <= a[i].c) {
                    d2[j+1] = min(d2[j+1], d[j] + a[i].w);
                    ans = max(ans, j + 1);
                }
            }
            d = d2;
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

