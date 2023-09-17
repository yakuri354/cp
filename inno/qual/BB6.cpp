// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 + 10;

ll a[maxn], b[maxn];
unordered_map<ll, ll> p;
unordered_map<ll, ll> p1;

void solve() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }

    copy(a, a + n, b);
    stable_sort(b, b + n);

    for (ll i = 0; i < n; i++) {
        p1[b[i]] = i;
    }

    ll z[] = {0, 0};
    for (ll i = 0; i < n; i++) z[p1[b[i]] % 2] += p1[b[i]] % 2 != p[b[i]] % 2;

    cout << max(z[0], z[1]) << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
