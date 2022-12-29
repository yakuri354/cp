// The GPLv3 License (GPLv3)
// Copyright (c) 2022 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// #pragma GCC optimize("Ofast")
//
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> leftev;
    vector<ll> rightev;
    vector<ll> leftodd;
    vector<ll> rightodd;
    vector<pair<ll, ll>> ts;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x & 1) {
            leftodd.push_back(x);
        } else {
            leftev.push_back(x);
        }
    }

    for (ll i = 0; i < m; i++) {
        ll x;
        cin >> x;
        if (x & 1) {
            rightodd.push_back(x);
        } else {
            rightev.push_back(x);
        }
    }

    sort(leftev.begin(), leftev.end());
    sort(leftodd.begin(), leftodd.end());
    sort(rightev.begin(), rightev.end());
    sort(rightodd.begin(), rightodd.end());
    
    for (ll i = 0; i < max(leftev.size(), rightev.size()); i++) {
        if (i >= leftev.size()) {
            ts.emplace_back(rightev[i], 0);
            continue;
        } 
        if (i >= rightev.size()) {
            ts.emplace_back(leftev[i], 0);
            continue;
        } 
        ll r = leftev[i], l = rightev[i];

        if (l <= r) {
            cerr << "    " << l << ' ' << r << endl;
            ts.emplace_back((l + r) / 2, (r - l) / 2);
        } else {
            ts.emplace_back(l, 0);
            ts.emplace_back(r, 0);
        }
    }

    for (ll i = 0; i < max(leftodd.size(), rightodd.size()); i++) {
        if (i >= leftodd.size()) {
            ts.emplace_back(rightodd[i], 0);
            continue;
        } 
        if (i >= rightodd.size()) {
            ts.emplace_back(leftodd[i], 0);
            continue;
        } 
        ll r = leftodd[i], l = rightodd[i];

        if (l <= r) {
            cerr << "    " << l << ' ' << r << endl;
            ts.emplace_back((l + r) / 2, (r - l) / 2);
        } else {
            ts.emplace_back(l, 0);
            ts.emplace_back(r, 0);
        }
    }

    for (auto [x, t] : ts) {
        cout << t << ' ' << x << '\n';
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
