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

ll binpow(ll b, ll e) {
    if (e == 0) return 1;

    if (e & 1) {
        return (b * binpow(b, e - 1)) % mod;
    } else {
        ll x = binpow(b, e / 2);
        return (x * x) % mod;
    }
}

void solve() {
    ll n;
    cin >> n;
    
    vector<ll> a = {inf};

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a.push_back(abs(x));
    }

    a.push_back(inf);

    auto center = min_element(a.begin(), a.end());

    if (!is_sorted(a.begin(), center, greater<>()) || !is_sorted(center, a.end())) {
        cout << 0 << endl;
        return;
    }

    cout << (count(a.begin(), a.end(), *center) + 1) % mod << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
}

