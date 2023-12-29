// #pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 1e5;
constexpr ll k = 333;

vector<vector<ll>> bs;

void solve() {
    ll n;
    cin >> n;
    
    bs.resize(k, vector<ll>(k));

    for (ll i = 0; i < n; i++) {
        cin >> bs[i / k][i % k];
    }
    
    ll q;
    cin >> q;

    for (ll bl = 0; bl * k <= q; bl++) {
        for (ll i = bl * k; i < q && i < (bl + 1) * k; i++) {

        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
