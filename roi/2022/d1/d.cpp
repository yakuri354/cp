// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

ll k;
vector<ll> dirs;

void solve() {
    ll n, w, h;
    cin >> n >> w >> h;

    vector<pll> pts;
    // pts.push_back({0, h});

    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        pts.push_back({x, y});
    }

    // pts.push_back({w, 0});

    sort(pts.begin(), pts.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    vector<pll> minstack = {{0, h}};

    for (ll i = 0; i < n; i++) {
        while (!minstack.empty() && pts[i].first <= minstack.back().first) minstack.pop_back();
        minstack.push_back(pts[i]);
    }

    ll lasty = h;
    ll ans = 0;
    for (auto [x, y]: minstack) {
        ans += (lasty - y) * (w - x);
        lasty = y;
    }

    cout << ans << endl;

    // ll ly = h, lx = ; for (auto [x, y]: pts) {

    // }
    // for (ll i = 1; i <= n; i++) {

    // }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> k;
    dirs.resize(k);

    for (ll& i : dirs)
        cin >> i;

    ll t;
    cin >> t;
    while (t-- > 0)
        solve();
}
