// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;
ll a[1000000];
ll t[2000000];

void build(ll n) {
    for (ll i = n - 1; i > 0; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
}

ll qmin(ll l, ll r, ll n) {
    ll ans = inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans = min(ans, t[l++]);
        if (r & 1) ans = min(ans, t[--r]);
    }
    return ans;
}

void solve() {
    ll n, ans;
    cin >> n;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << a[0] << endl;
        return;
    }

    ans = a[0];

    stack<pair<ll, ll>> s;
    s.push({0, -1});
    for (ll i = 0; i < n; i++) {
        while (a[i] <= s.top().first && s.size() > 1) {
            auto [top, ti] = s.top();
            s.pop();

            ans = max(ans, (i - s.top().second - 1) * top);
        }
        if (a[i] == 0) s.pop();
        if (a[i] == 0 || a[i] > s.top().first) {
            s.emplace(a[i], i);
        }
    }

    while (s.size() > 1) {
        auto [top, ti] = s.top();
        s.pop();

        ans = max(ans, (n - s.top().second - 1) * top);
    }

    cout << ans << endl;
}
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
