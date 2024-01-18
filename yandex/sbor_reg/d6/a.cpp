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

const ll MOD = 1e9 + 7;

ll mod(ll x) {
    return ((x % MOD) + MOD) % MOD;
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n), fac(n+1), p(n+1);

    fac[0] = fac[1] = 1;
    p[0] = 1;
    for (ll i = 1; i <= n; i++) {
        p[i] = mod(p[i-1] * 2);
        fac[i] = mod(fac[i-1] * i);
    }

    for (ll &i: a) cin >> i;

    unordered_map<ll, ll> cnt;
    for (ll &i: a) cnt[i]++;

    ll ans = 1;

    ll maxv = *max_element(a.begin(), a.end());
    cnt[maxv]--;

    for (auto &[k, v]: cnt) {
        ans = mod(ans * fac[v + 1]);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

