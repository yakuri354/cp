#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll maxn = 1e5;

ll a[maxn];


void solve() {
    ll n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        a[i] = -x;
    }
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        a[i] += x;
    }

    sort(a, a + n, greater<>());

    ll lo = 0, hi = n - 1, ans = 0;

    while (lo < hi) {
        while (a[lo] + a[hi] < 0 && lo < hi) hi--;
        if (lo >= hi) break;
        ans++; lo++; hi--;
    }

    cout << ans << endl;
}

int main() {
    ll t;
    cin >> t;
    while (t --> 0) solve();
}