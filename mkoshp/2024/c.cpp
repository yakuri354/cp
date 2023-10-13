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

const ll inf = INT32_MAX;

void solve() {
    ll k;
    cin >> k;

    ll sa = 0;
    for (ll i = 0; i < k; i++) {
        ll x;
        cin >> x;
        sa += x;
    }
    
    ll mina = inf, maxa = -inf;
    for (ll i = max(k + 1, 3ll); i < 100000; i++) {
        ll other = 180 * (i - 2) - sa;
        
        if (i - k <= other && other <= (i - k) * 179) {
            mina = min(i, mina);
            maxa = max(i, maxa);
        }
    }
    
    if (mina == inf) {
        cout << -1 << endl;
    } else {
        cout << mina << ' ' << maxa << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
