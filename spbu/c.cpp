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

ll mod(ll x, ll m) {
    return (x % m + m) % m;
}

struct hasher {
    ll n, P, M;
    vector<ll> p, h;

    hasher(ll P, ll M, string& s): n(s.size()), P(P), M(M) {
        p.assign(n + 1, 1);
        p[0] = 1;
        for (ll i = 1; i <= n; i++) {
            p[i] = mod(p[i-1] * P, M);
        }

        h.assign(n + 1, 0);
        h[0] = mod(p[n-1] * s[0], M);
        for (ll i = 1; i < n; i++) {
            h[i] = mod(h[i-1] + mod(p[n-i-1] * s[i], M), M);
        }
    }

    ll hash_sub(ll i, ll sz) {
        if (i == 0) {
            return h[sz - 1];
        } else {
            return mod(mod(h[i + sz - 1] - h[i - 1], M) * p[i], M);
        }
    }

    ll hash_all() {
        return h.back();
    }
};

// 6 79461 79461 79461 79461

vector<ll> mds = {
    ll(1e9) + 7, 
    ll(1e9) + 9,
    ll(1e9) + 21,
    ll(1e9) + 33,
    // ll(1e9) + 7
};

ll p0 = 1009;

// 6 79461 79461 79461 79461
// 6 433675845 321881664 651135331 980421134 

void first() {
    ll n;
    cin >> n;
    string s;
    cin >> s;

    s += s;
    
    // for (ll i = 0; i < s.size(); i++) {
    //     s[i] -= '0';
    // }

    cout << n << ' ';
    for (ll m: mds) {
        hasher h0(p0, m, s);
        cout << h0.hash_sub(0, n) << ' ';
    }
    cout << endl;
}

void second() {
    ll n;
    cin >> n;
    string t;
    cin >> t;

    ll old_n;
    cin >> old_n;

    vector<ll> hss(mds.size());
    for (ll &i: hss) cin >> i;

    if (n != old_n) {
        cout << "NO" << endl;
        return;
    }

    // cout << "YES" << endl; return;

    t += t;

    // for (auto &i: t) i -= '0';

    vector<hasher> z;
    for (ll m: mds) {
        z.push_back(hasher(p0, m, t));
    }

    for (ll i = 0; i < n; i++) {
        bool ok = true;
        for (ll j = 0; j < mds.size(); j++) {
            ok &= (z[j].hash_sub(i, n) == hss[j]);
        }
        if (ok) {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
    return;
}

void solve() {
    string l;
    cin >> l;

    if (l == "first") {
        first();
    } else {
        second();
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}


