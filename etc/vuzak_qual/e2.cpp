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
#include <bitset>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
const ll maxw = 1e6 / 2;

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    ll sum_a = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        sum_a += a[i];
    }

    if (sum_a & 1) {
        cout << "NO" << endl;
        return;
    }

    vector<ll> p(n);
    bitset<maxw> b;

    for (ll i = 0; i < n; i++) {
        auto b2 = b;
        b |= b << a[i];

        bitset<maxw> d = b2 xor b;

        for (ll x = d._Find_first() ; x < maxw; x = d._Find_next(x)) p[x] = i;
    }

    if (b[sum_a / 2]) {
        cout << "YES" << '\n';
        vector<bool> plus(n);
        vector<ll> a1;
        set<ll> a2;

        ll curr = sum_a / 2;
        while (curr > 0) {
            a1.push_back(p[curr]);
            a2.insert(p[curr]);
            curr -= a[p[curr]];
        }

        stable_sort(a1.begin(), a1.end());

        cout << a[0];
        for (ll i = 1; i < a1[0] - 1; ++i) {
            cout << '+';
            cout << a[i];
        }

        cout << '=' << a[a1[0]];

        for (ll i = a1[0] + 1; i < n; ++i) {
            if (a2.count(i)) {
                cout << '+';
            } else {
                cout << '-';
            }
            cout << a[i];
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
        return;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

