// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 50;

void solve() {
    ll n;
    cin >> n;

    vector<pair<ll, ll>> pts;

    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;

        pts.push_back({x, y});
    }

    ll h, v;
    cin >> h >> v;
    
    vector<ll> hs = {-inf, inf}, vs = {-inf, inf};

    for (ll i = 0; i < h; i++) {
        ll x;
        cin >> x;

        hs.push_back(x);
    }
    
    sort(hs.begin(), hs.end());

    for (ll i = 0; i < v; i++) {
        ll x;
        cin >> x;

        vs.push_back(x);
    }

    sort(vs.begin(), vs.end());

    map<ll, ll> cnt;

    for (ll i = 0; i < n; i++) {
        ll hi = upper_bound(hs.begin(), hs.end(), pts[i].second) - hs.begin();
        ll vi = upper_bound(vs.begin(), vs.end(), pts[i].first) - vs.begin();

        cnt[hi * ll(1e9) + vi]++;
    }

    ll ans = 0;
    for (auto &[k, v]: cnt) {
        ans = max(ans, v);
    }

    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

