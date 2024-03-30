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

void solve() {
    ll n;
    cin >> n;

    vector<ll> p(n);
    for (ll &i: p) cin >> i;

    vector<ll> linv(n), rinv(n);
    
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            rinv[i] += p[j] < p[i];
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < i; j++) {
            linv[i] += p[j] > p[i];
        }
    }
    
    ll ans = 0;

    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            ll x = max(abs(p[i] - p[j]), j - i + max(rinv[j], linv[i]));
            // cout << i + 1 << ' ' << j + 1 << " -> " << x << endl;
            ans += x;
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

