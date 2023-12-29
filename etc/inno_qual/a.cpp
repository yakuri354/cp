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

const fl eps = 1e-8;

void solve() {
    ll n, q, x;
    cin >> n >> q >> x;
    vector<fl> ts(q);

    for (ll i = 0; i < n; i++) {
        ll ty, mass, k;
        cin >> ty >> mass >> k;

        ts[ty - 1] += fl(mass) * fl(k) / fl(100.0);
    }

    sort(ts.begin(), ts.end(), greater<>());

    fl res = 0;
    ll ans = 0;
    for (ll i = 0; i < q; i++) {
        if (res + eps > fl(x)) break;
        res += ts[i];
        ans++;
    }

    if (res + eps < fl(x)) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

