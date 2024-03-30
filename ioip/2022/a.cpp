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

vector<ll> divs(ll x) {
    vector<ll> res;
    for (ll i = 2; i * i <= x; i++) {
        while (x % i == 0) {
            x /= i;
            res.push_back(i);
        }
    }

    if (x != 1) res.push_back(x);

    sort(res.begin(), res.end());

    return res;
}

void solve() {
    ll a, b;
    cin >> a >> b;

    auto da = divs(a);

    ll ans = (a - b % a) % a;
    for (ll x: da) {
        ans = min(ans, (x - b % x) % x);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}

