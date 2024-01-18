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

template <typename T, typename Cmp = less<T>>
struct sparse {
    ll lg = 21, n;
    vector<ll> tbl;

    sparse(vector<ll> v): n(v.size()), tbl(n * lg) {
        for (ll i = 0; i < n; i++) {
            tbl[i] = v[i];
        }

        for (ll l = 1; l < lg; l++) {
            for (ll i = 0; i + (1 << l) < n; i++) {
                tbl[n * l + i] = min(tbl[n * (l - 1) + i], tbl[n * (l - 1) + i + (1 << (l - 1))], Cmp());
            }
        }
    }

    ll rmq(ll l, ll r) {
        for (ll k = lg - 1; k >= 0; k--) {
            if (l + (1 << k) <= r) {
                return min(tbl[k * n + l], tbl[k * n + r - (1 << k)], Cmp());
            }
        }

        exit(-1);
    }
};

void solve() {
    ll n;
    cin >> n;

    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

