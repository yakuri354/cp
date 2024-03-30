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

ll n, k, m;

ll mod(ll x) {
    return x % m;
}

ll ipw(ll b, ll p) {
    if (p == 0) {
        return 1;
    }
    if (p == 1) {
        return mod(b);
    }

    if (p % 2 == 0) {
        ll z = ipw(b, p / 2);
        return mod(z * z);
    } else {
        return mod(ipw(b, p - 1) * b);
    }
}

ll cnk(ll n, ll k) {
    if (n < k) {
        return 0;
    }

    ll fn = 1;
    ll zs = 0;
    for (ll i = n; i > n - k; i--) {
        ll z = i;
        while (z % m == 0) {
            zs++;
            z /= m;
            continue;
        }
        fn = mod(z * fn);
    }

    ll fk = 1;
    ll zsk = 0;
    for (ll i = 1; i <= k; i++) {
        ll z = i;
        while (z % m == 0) {
            zsk++;
            z /= m;
            continue;
        }
        fk = mod(z * fk);
    }

    zs -= zsk;

    if (zs > 0) {
        return 0;
    }

    return mod(fn * ipw(fk, m - 2));
}

void solve() {
    cin >> n >> k >> m;

    if (m == 1) {
        cout << 0 << endl;
        return;
    }

    cout << cnk(n - k + 1, k) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
