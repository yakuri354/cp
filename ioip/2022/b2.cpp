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

const ll inf = 1e12;

const ll mod = 998244353;

ll solve3(vector<ll> &a) {
    ll n = a.size();
    ll ans = 0;
    for (ll m = 0; m < 1ll << n; m++) {
        auto b = a;

        for (ll i = 0; i < n; i++) {
            if ((m >> i) & 1) b[i] *= -1;
        }

        if (is_sorted(b.begin(), b.end())) {
            ans++;
        }
    }

    return ans;
}

ll binpow(ll b, ll e) {
    if (e == 0) return 1;

    if (e & 1) {
        return (b * binpow(b, e - 1)) % mod;
    } else {
        ll x = binpow(b, e / 2);
        return (x * x) % mod;
    }
}


ll solve(vector<ll> a) {
    a.insert(a.begin(), inf);
    a.push_back(inf);
    for (ll &i: a) i = abs(i);

    auto center = min_element(a.begin(), a.end());

    if (!is_sorted(a.begin(), center, greater<>()) || !is_sorted(center, a.end())) {
        return 0;
    }

    if (*center != 0) {
        return (count(a.begin(), a.end(), *center) + 1) % mod;
    } else {
        return binpow(2, count(a.begin(), a.end(), 0));
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ll n;
    cin >> n;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    cout << solve(a) << endl;

    // mt19937_64 mt(random_device{}());
    // uniform_int_distribution<ll> xd(-10, 10);

    // for (ll it = 0;; it++) {
    //     vector<ll> a(n);
    //     for (ll &i: a) i = xd(mt);

    //     ll smart = solve(a);
    //     ll dumb = solve3(a);
    //     if (smart != dumb) {
    //         cout << "kal" << endl;
    //         solve(a);
    //     }
    // }
}

