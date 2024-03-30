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

ll mod(ll x, ll m) {
    return ((x % m) + m) % m;
}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> a(n), b(m);
    for (ll &i: a) cin >> i, i--;
    for (ll &i: b) cin >> i, i--;

    if (n < m) {
        swap(n, m);
        swap(a, b);
    }

    ll maxa = 2 * n;

    vector<ll> binv(maxa);
    vector<bool> in_b(maxa);

    for (ll i = 0; i < m; i++) {
        binv[b[i]] = i;
        in_b[b[i]] = true;
    }

    ll g = __gcd(ull(n), ull(m));
    ll P = (n * m) / g;

    vector<ll> from(n, m);

    for (ll i = 0; i < n; i++) {
        if (in_b[a[i]]) {
            from[mod(i-binv[a[i]], n)]--;
        }
    }

    ll period_cnt = 0;
    ll period_sz = 0;

    // for (ll i = 0; i < n; i += g) {
    //     period_cnt += from[i];
    // }

    {
        ll i = mod(m, n);
        period_sz = m;
        period_cnt += from[0];
        while (i != 0) {
            period_cnt += from[i];
            period_sz += m;
            i = mod(i + m, n);
        }
    }

    ll ans = 0;

    ans += period_sz * (max(k - 1, 0ll) / period_cnt);
    k -= period_cnt * (max(k-1, 0ll) / period_cnt);

    // while (k > period_cnt) {
    //     k -= period_cnt;
    //     ans += period_sz;
    // }

    ll i = 0;
    while (k > from[i]) {
        k -= from[i];
        ans += m;
        i = mod(i + m, n);
    }

    for (ll j = 0; k > 0; i = mod(i + 1, n), j = mod(j + 1, m)) {
        ans++;
        if (a[i] != b[j]) k--;
    }

    cout << ans  << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

