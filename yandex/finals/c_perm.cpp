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
#include <fstream>

using namespace std;

#ifndef DBG
#define cerr if (0) cerr
#endif

using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

vector<fl> pref_avg(const vector<ll> &x) {
    vector<fl> pa(x.size());
    fl sum = 0;
    for (ll i = 0; i < x.size(); i++) {
        sum += x[i];
        pa[i] = sum / fl(i + 1);
    }
    return pa;
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> p(n);
    for (ll &x: p) cin >> x, x--;

    bool id = true;

    vector<ll> pinv(n);
    for (ll i = 0; i < n; i++) pinv[p[i]] = i, id = id && p[i] == i;

    if (id) {
        cout << 1 << endl;
        return;
    }

    vector<ll> diff(n);
    for (ll i = 0; i < n; i++) {
        diff[i] = pinv[i] - i;
    }

    cout << -*min_element(diff.begin(), diff.end()) + 1 << endl;
}

// 0 1 2 3 
// x ^___v

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

