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

void solve() {
    ll n;
    string s;
    cin >> n >> s;

    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        if (s[i] == '-') a[i] = -1;
        else a[i] = 1;
    }

    vector<ll> p(n);
    partial_sum(a.begin(), a.end(), p.begin());

    ll curr = 0, last = 0, saved = 0;
    for (ll i = 0; i < n; i++) {
        curr += a[i];
        if (curr == 0) {
            saved += i - last + 1;
            last = i + 1;
        }
    }

    if (last != n) {
        saved += (n - last) - abs(curr);
    }

    cout << n - saved << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0) solve();
}

