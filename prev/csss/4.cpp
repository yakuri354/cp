// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll maxn = 1e5;

ll a[maxn];

bool square(ll x, ll &rt) {
    ll lo = 0, hi = 2 * ll(sqrt(x));
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;
        if (m * m <= x) lo = m;
        else hi = m;
    }

    if (lo * lo == x) {
        rt = lo;
        return true;
    } else {
        return false;
    }
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> ans;

    for (ll i = 0; i < n / 2; i++) {
        cin >> a[i];
    }

    ll lastsq = 0;

    for (ll i = 0; i < n / 2; i++) {
        ll sq = lastsq;
        ll newsq;
        while (!square(sq * sq + a[i], newsq) && sq <= ll(1e6)) sq++;
        // cerr << "at " << i << " " << sq << " -> " << sq * sq << endl;
        if (sq > ll(1e6)) {
            cout << "No\n";
            return;
        }
        ans.push_back(sq * sq - lastsq * lastsq);
        if (ans.back() > ll(1e13)) assert(0);
        lastsq = newsq;
    }

    cout << "Yes\n";

    for (ll i = 0; i < n/2; i++) cout << ans[i] << ' ' << a[i] << ' ';

    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
