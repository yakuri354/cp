// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using fl = long double;

const ll inf = INT32_MAX;

ll a[100000];

ll gcd(ll a , ll b)
{
   if(b==0) return a;
   a%=b;
   return gcd(b,a);
}

void solve() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = abs(a[0] - a[n-1]);
    for (ll i = 0; i < n / 2; i++) {
        ans = gcd(ans, abs(a[i]-a[n-i-1]));
    }

    cout << ans << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    ll t; cin >> t; while (t --> 0)
        solve();
}
