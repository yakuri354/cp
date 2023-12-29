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
    ll n, t;
    cin >> n >> t;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    sort(a.begin(), a.end());

    ll cnt = 0;
    for (ll i: a) {
        if (i <= t) {
            t -= i;
            cnt++;
        } else {
            break;
        }
    }

    cout << cnt << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

