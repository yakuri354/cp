// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5 / 2 + 1;

ll a[maxn];

bool is_sq(ll x) {
    fl s = round(sqrtl(fl(x)));
    return abs(s * s - fl(x)) < 1e-9;
}

void solve() {
    ll n;
    cin >> n;

    n /= 2;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> ans;

    ll pref_rt = 0;
    for (ll i = 0; i < n; i++) {
        ll new_rt = pref_rt;
        while (!is_sq(new_rt * new_rt + a[i])) {
            if (new_rt > ll(1e6) || 2 * new_rt + 1 > a[i]) {
                cout << "No\n";
                return;
            } else {
                new_rt++;
            }
        }

        ans.push_back(new_rt * new_rt - pref_rt * pref_rt);
        if (ans.back() > ll(1e13)) exit(-1);
        pref_rt = ll(round(sqrtl(new_rt * new_rt + a[i])));
    }

    cout << "Yes" << endl;
    for (ll i = 0; i < n; i++) {
        cout << ans[i] << ' ' << a[i] << ' ';
    }
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
