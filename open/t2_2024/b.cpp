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

    n++;

    vector<ll> d(n), l(n), r(n), pd(n+1), l1(n), r1(n);

    for (ll i = 1; i < n; i++) {
        cin >> d[i];
    }
    for (ll i = 1; i < n; i++) {
        cin >> l[i];
    }
    for (ll i = 1; i < n; i++) {
        cin >> r[i];
    }

    ll a0, b0;
    cin >> a0 >> b0;

    pd[n-1] = d[n-1];
    for (ll i = n - 2; i > 0; i--) {
        pd[i] = pd[i+1] + d[i];
    }
    
    l1[0] = a0 + pd[1];
    for (ll i = 1; i < n; i++) {
        l1[i] = l[i] + pd[i+1];
    }

    r1[0] = b0 + pd[1];
    for (ll i = 1; i < n; i++) {
        r1[i] = r[i] + pd[i+1];
    }

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

