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

    vector<ll> to_l_ev;
    vector<ll> to_l_odd;
    vector<ll> to_r_ev;
    vector<ll> to_r_odd;

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x % 2 == 0) {
            to_l_ev.push_back(x);
        } else {
            to_l_odd.push_back(x);
        }
    }

    for (ll i = 0; i < m; i++) {
        ll x;
        cin >> x;
        if (x % 2 == 0) {
            to_r_ev.push_back(x);
        } else {
            to_r_odd.push_back(x);
        }
    }

    reverse(to_l_ev.begin(), to_l_ev.end());
    reverse(to_l_odd.begin(), to_l_odd.end());

    {
        ll lp = 0, rp = 0;

        while (lp < to_l_ev.size() || rp < to_r_ev.size()) {
            if (lp >= to_l_ev.size()) {
                cout << 0 << ' ' << to_r_ev[rp] << '\n';
                rp++;
                continue;
            }
            if (rp >= to_r_ev.size()) {
                cout << 0 << ' ' << to_l_ev[lp] << '\n';
                lp++;
                continue;
            }
            ll to_l = to_l_ev[lp], to_r = to_r_ev[rp];
            if (to_l < to_r) {
                cout << 0 << ' ' << to_l << '\n';
                lp++;
                continue;
            }
            cout << (to_l - to_r) / 2 << ' ' << (to_l + to_r) / 2 << '\n';
            lp++;
            rp++;
        }
    }
    {
        ll lp = 0, rp = 0;

        while (lp < to_l_odd.size() || rp < to_r_odd.size()) {
            if (lp >= to_l_odd.size()) {
                cout << 0 << ' ' << to_r_odd[rp] << '\n';
                rp++;
                continue;
            }
            if (rp >= to_r_odd.size()) {
                cout << 0 << ' ' << to_l_odd[lp] << '\n';
                lp++;
                continue;
            }
            ll to_l = to_l_odd[lp], to_r = to_r_odd[rp];
            if (to_l < to_r) {
                cout << 0 << ' ' << to_l << '\n';
                lp++;
                continue;
            }
            cout << (to_l - to_r) / 2 << ' ' << (to_l + to_r) / 2 << '\n';
            lp++;
            rp++;
        }
    }
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
