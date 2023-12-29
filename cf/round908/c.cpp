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

const ll inf = 1ll << 50;

ll mod(ll x, ll m) {
    return (m + x % m) % m;
}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    vector<bool> used(n);

    for (ll &i: a) cin >> i;

    ll dist = 0;
    for (ll i = n - 1; a[i] <= n; i = mod(i - a[i], n)) {
        if (used[i]) {
            dist = inf;
            break;
        }
        used[i] = true;
        dist++;
    }

    if (k <= dist) {
        cout << "Yes" << '\n';
    } else {
        cout << "No" << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

