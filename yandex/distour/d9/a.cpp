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

struct ev {
    bool to_r;
    ll x, color;
};

void solve() {
    ll n, k, l;

    cin >> n >> k >> l;

    vector<ev> evs;

    for (ll i = 0; i < n; i++) {
        ll x, color;
        string dir;
        cin >> x >> color >> dir;
        if (dir == "L") {
            evs.push_back({false, x, color});
        }
        if (dir == "D") {
            evs.push_back({true, x, color});
        }
    }

    vector<ll> paths(k);
    vector<ll> ans(k);

    ll last = 0;
    ll pref = 0;
    ll first_r = -1;
    for (ll i = 0; i < n; i++) {
        auto e = evs[i];
        
        if (e.to_r) {
            if (first_r == -1) first_r = e.x;
            ans[e.color] += (l - e.x) * 2;
            vector<ll> pn = paths;
            for (ll i = 0; i < k; i++) {
                paths[(i + e.color) % k] = pn[i];
            }
            paths[e.color] += e.x - last;
            pref = (pref + e.color) % k;
            last = e.x;
        } else {
            ans[e.color] += e.x - last;
            for (ll i = 0; i < k; i++) {
                ans[(e.color + i) % k] += paths[i];
            }
            if (first_r != -1) ans[(pref + e.color) % k] += e.x + first_r;
            else ans[(pref + e.color) % k] += e.x - last;
        }
    }

    for (ll i = 0; i < k; i++) {
        cout << fl(ans[i]) / 2 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

