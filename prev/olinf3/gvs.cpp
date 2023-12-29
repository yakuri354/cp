#include "bits/stdc++.h"

using namespace std;
using ll = long long;

pair<ll, ll> a[100000];

int main() {
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
    sort(a, a + n, [](auto x, auto y) {
            if (x.first == y.first)
                return x.second < y.second;
            else
                return x.first > y.first;
            });
    for (ll i = 0; i < n; i++) cout << a[i].second << ' ' << a[i].first << '\n';
}
