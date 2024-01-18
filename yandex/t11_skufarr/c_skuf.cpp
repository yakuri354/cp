// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

vector<ll> skuf(string &s) {
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

    return cls;
}

void solve() {
    string s;
    cin >> s;

    ll k;
    cin >> k;
    k--;

    const ll n = s.size();

    auto c = skuf(s);

    map<ll, ll> m;

    for (ll i = 0; i < n; i++) {
        m[c[i]] = i;
    }

    if (k < m.size()) {
        auto it = m.begin();
        for (ll i = 0; i < k; i++) it++;
        rotate(s.begin(), s.begin() + it->second, s.end());
        cout << s << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

