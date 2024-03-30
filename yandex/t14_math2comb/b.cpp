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

const ll maxn = 1e5 + 1;

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

ll fac[maxn], faci[maxn];

ll cnk(ll n, ll k) {
    return mod(mod(fac[n] * faci[n - k]) * faci[k]);
}

void solve() {
    cin >> n >> k >> m;

    fac[0] = 1;
    faci[0] = 1;
    for (ll i = 1; i < min(m, maxn); i++) {
        fac[i] = mod(fac[i-1] * i);
        faci[i] = ipw(fac[i], m - 2);
        // if (mod(fac[i] * faci[i]) != 1) {
        //     exit(-1);
        // }
    }

    cout << cnk(n - k + 1, k) << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
