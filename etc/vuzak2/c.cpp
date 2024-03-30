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
    ll n, q;
    cin >> n >> q;

    vector<pair<ll, bool>> a;
    for (ll i = 0; i < q; i++) {
        ll x, d;
        cin >> x >> d;

        a.push_back({max(x - d, 1ll), true});
        a.push_back({min(x + d + 1, n + 1), false});
    }

    sort(a.begin(), a.end());

    ll last = 0, cov = 0;
    ll sum = 0;
    for (auto &[x, ty]: a) {
        if (cov > 0) sum += x - last;

        if (ty) {
            cov++;
        } else {
            cov--;
        }

        last = x;
    }

    cout << n - sum << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

