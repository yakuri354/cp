// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll subs(const string& s, const string& t) {
    string z = t + '#' + s;
    ll n = ll(z.size());
    vector<ll> p(n, 0);
    for (ll i = 1; i < n; i++) {
        ll cur = p[i - 1];
        while (z[i] != z[cur] && cur > 0)
            cur = p[cur - 1];
        if (z[i] == z[cur])
            p[i] = cur + 1;
    }

    ll ans = 0;
    for (ll x : p) {
        if (x >= t.size()) ans++;
    }
    return ans;
}

void solve() {
    string big, small;
    cin >> big >> small;

    ll ans = 0, k = 0;

    for (ll i = 1; i <= big.size(); i++) {
        string g;
        for (ll j = 0; j < big.size(); j += i) g += big[j];

        if (g.size() < small.size()) break;

        ll z = subs(g, small);
        if (z > ans) {
            ans = z;
            k = i;
        }
    }

    cout << k << '\n';
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
    cout << flush;
}
