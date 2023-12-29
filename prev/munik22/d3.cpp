// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<pair<ll, bool>> evs;
    vector<pair<ll, bool>> evs2;
    stack<ll> zz;

    for (ll i = 0; i < n; i++) {
        // cin >> to_l[i];
        ll x;
        cin >> x;
        if (x % 2 == 0)
            evs.emplace_back(x, true);
        else
            evs2.emplace_back(x, true);
    }
    for (ll i = 0; i < m; i++) {
        // cin >> to_r[i];
        ll x;
        cin >> x;
        if (x % 2 == 0)
            evs.emplace_back(x, false);
        else
            evs2.emplace_back(x, false);
    }

    // reverse(to_l.begin(), to_r.end());

    // ll lp = 0, rp = 0;
    
    // while (lp < n && rp < m) {
          // 
    // }
    //

    sort(evs.begin(), evs.end());

    for (auto [x, ty] : evs) {
        if (ty) {
            // nalevo
            
            if (zz.empty()) {
                cout << 0 << ' ' << x << endl;
                continue;
            }

            ll other = zz.top();
            zz.pop();

            cout << (x - other) / 2 << ' ' << (x + other) / 2 << endl;
        } else {
            zz.push(x);
        }
    }

    while (!zz.empty()) {
        ll x = zz.top();
        zz.pop();
        cout << 0 << ' ' << x << endl;
    }

    sort(evs2.begin(), evs2.end());

    for (auto [x, ty] : evs2) {
        if (ty) {
            // nalevo
            
            if (zz.empty()) {
                cout << 0 << ' ' << x << endl;
                continue;
            }

            ll other = zz.top();
            zz.pop();

            cout << (x - other) / 2 << ' ' << (x + other) / 2 << endl;
        } else {
            zz.push(x);
        }
    }

    while (!zz.empty()) {
        ll x = zz.top();
        zz.pop();
        cout << 0 << ' ' << x << endl;
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
