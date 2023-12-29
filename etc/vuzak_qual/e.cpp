// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1e3;
const ll zw = 3e3;
const ll maxw = 2 * zw + 1;

ll d[];
ll p[];

void solve() {
    ll n;
    cin >> n;

    n--;

    ll a1;
    cin >> a1;

    vector<ll> a(n);
    ll sum2 = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        sum2 += a[i];
        a[i] *= 2;
    }

    d[0] = 1;
    for (ll i = 0; i < n; i++) {
        for (ll w = a[i]; w < ) {
            if (d[maxw + w] == 1) continue;
            if (d[maxw + w-a[i]] == 1) {
                d[maxw + w] = 1;
                p[maxw + w] = a[i];
            }
        }
    }

    if (d[sum2 - a1]) {
        vector<bool> plus(n);

    } else {
        cout << "NO" << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

