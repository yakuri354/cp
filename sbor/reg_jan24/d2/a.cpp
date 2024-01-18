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

const ll inf = 1e9;

pair<vector<ll>, vector<ll>> skuf(string &s) {
    ll n = s.size();

    vector<ll> cls(n);
    for (ll i = 0; i < n; i++) {
        cls[i] = s[i];
    }

    for (ll l = 1; l < n * 2; l *= 2) {
        vector<pair<ll, ll>> z;
        for (ll i = 0; i < n; i++) {
            z.push_back({cls[i] * 1000000000ll + cls[(i + l) % n], i});
        }

        sort(z.begin(), z.end());

        ll c = 0;
        cls[z[0].second] = 0;
        for (ll i = 1; i < n; i++) {
            if (z[i].first != z[i - 1].first) {
                c++;
            }
            cls[z[i].second] = c;
        }
    }

    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        p[cls[i]] = i;
    }

    return {p, cls};
}

struct segt_min {
    ll n;
    vector<ll> t;

    segt_min(ll n): n(n), t(n * 2) { }
    segt_min(vector<ll> &a): n(a.size()), t(n * 2) {
        copy(a.begin(), a.end(), t.begin() + n);
        for (ll i = n - 1; i > 0; i--) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }

    ll query(ll l, ll r) {
        ll res = inf;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) 
        }
    }
};

void solve() {
    string s;
    cin >> s;

    auto [p, cls] = skuf(s);
    

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

