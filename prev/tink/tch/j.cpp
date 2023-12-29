// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll seqsum(ll b, ll l) {
    ll ans = 0;
    ll z = 1;
    for (ll i = 0; i <= l; i++) {
        ans += z;
        if (z > INT64_MAX / l) return -1;
        z *= l;
    }
    return ans;
}

ll find_prod(ll val, ll l) {
    ll lo = 2, hi = 1e11;
    while (lo < hi) {
        ll m = (lo + hi) / 2;

        ll ss = seqsum(m, l);
        if (ss == -1 || ss > val) hi = m - 1;
        else lo = m;
    }

    if (seqsum(lo, l) == val) return lo;

    return -1;
}

void solve() {
    ll n, n1, k;
    cin >> n >> k;
    n1 = n;

    map<ll, ll> divs;

    for (ll i = 2; i * i <= n1 && n > 1;) {
        if (n % i == 0) {
            n /= i;
            divs[i]++;
        } else {
            i++;
        }
    }

    if (n != 1) divs[n]++;

    
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
