// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <ctime>
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


void solve() {
    string x;
    ll y;
    cin >> x >> y;

    const ll n = x.size();

    vector<ll> p10(17);

    p10[0] = 1;
    for (ll i = 1; i < 17; i++) {
        p10[i] = p10[i-1] * 10ll;
    }

    if (y == 1) {
        sort(x.begin(), x.end(), greater<>());
        cout << x << '\n';
        return;
    }

    /// l < r
    auto cmp = [&](ll l, ll r) {
        if (x[l] >= x[r]) return false;

        ll pwrl = n - 1 - l, pwrr = n - 1 - r;
        ll lv = x[l] - '0', rv = x[r] - '0';
        ll old = lv * p10[pwrl] + rv * p10[pwrr];
        ll nww = rv * p10[pwrl] + lv * p10[pwrr];
        return pwrl > 16 || nww - old >= y * (r - l);
    };

    vector<pll> a;
    for (ll i = 0; i < x.size(); i++) a.push_back({x[i] - '0', i});

    if (a.size() > 20) {
        sort(a.begin(), a.end() - 20);
    }

    while (true) {
        bool chng = false;
        for (ll l = max(0ll, n - 20); l < n; l++) {
            for (ll r = l + 1; r < n; r++) {
                if (cmp(l, r)) {
                    swap(x[l], x[r]);
                    chng = true;
                }
            }
        }
        if (chng == false) break;
    }

    cout << x << '\n';

    // stable_sort(a.begin(), a.end(), [](auto l, auto r) {
    //     // l < r

    //     if (l.second < r.second) {
    //         if (l.first >= r.first) return true;
    //         else {
    //             // try to swap

    //             if (r.second < l.second >= 16)
    //         }
    //     }
    // });
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

