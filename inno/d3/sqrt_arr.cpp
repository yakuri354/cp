// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 5e5;
constexpr ll k = 710;

const ll inf = INT32_MAX;

vector<vector<ll>> a;
vector<ll> bs;

void recalc(ll bl) {
    bs[bl] = *min_element(a[bl].begin(), a[bl].end());
}

ll minseg(ll l, ll r) {
    ll ans = inf;
    for (ll i = l; i < r;) {
        if (i % k == 0 && i + k <= r) {
            ans = min(ans, bs[i / k]);
            i += k;
        } else {
            ans = min(ans, a[i / k][i % k]);
            i++;
        }
    }
    
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    
    a.resize(k, vector<ll>(k));
    bs.resize(k);

    for (ll i = 0; i < n; i++) {
        cin >> a[i / k][i % k];
    }
    
    for (ll i = 0; i < k; i++) {
        recalc(i);
    }
    
    string qt;
    while (cin >> qt) {
        if (qt == "set") {
            ll i, x;
            cin >> i >> x;
            i--;
            a[i / k][i % k] = x;
            recalc(i / k);
        }
        if (qt == "min") {
            ll i, j;
            cin >> i >> j;
            i--;
            
            cout << minseg(i, j) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
