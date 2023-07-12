// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[100001];
ll pl[100001];
ll pr[100001];

void solve() {
    ll n, m;
    cin >> n >> m;
    set<ll> bootstrap;

    ll toleft = 0, toright = 0;
    for (ll i = 0; i <= m; i++) pl[i] = 0, pr[i] = 0;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) {
            a[i] -= 1;
            pl[a[i]] = 1;
            pr[a[i]] = 1;
            bootstrap.insert(a[i]);
        }

        if (a[i] == -1) toleft++;
        if (a[i] == -2) toright++;
    }

    bootstrap.insert(-1);
    bootstrap.insert(m);
    
    for (ll i = 0; i < m; i++) {
        if (i > 0) pl[i] += pl[i-1];
    }

    for (ll i = m-1; i >= 0; i--) {
        if (i < n-1) pr[i] += pr[i+1];
    }

    ll ans1 = -inf;
    for (ll i : bootstrap) {
        ll ans = 0;
        ans += bootstrap.size() - 2; 

        ll right = max(m - i - 1, 0ll), left = max(i, 0ll);

        if (i < m - 1) right -= pr[i+1];
        if (i > 0) left -= pl[i-1];

        ans += min(right, toright) + min(left, toleft);
        ans1 = max(ans1, ans);
    }

    cout << ans1 << '\n';
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
    solve();
}
