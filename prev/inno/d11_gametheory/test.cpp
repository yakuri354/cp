// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iomanip>
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
const fl eps = 1e-9;

ll grundy(ll n) {
    vector<ll> d(1 << n);
    vector<ll> mex(1 << n, -1);
    ll t = 0;
    
    for (ll m = 1; m < 1 << n; m++) {
        t++;
        for (ll i = 0; i < n; i++) {
            if (!(m & (1 << i))) continue;
            ll m2 = m;
            for (ll j = i + 1; j <= n; j += (i + 1)) {
                m2 &= ~(1 << (j - 1));
            }
            mex[d[m2]] = t;
        }
        
        ll res = 0;
        for (ll i = 0; i < 1 << n; i++) {
            if (mex[i] == t) continue;
            res = i;
            break;
        }
        
        d[m] = res;
    }
    
    return d[(1 << n) - 1];
}

void solve() {
    ll n;
    cin >> n;
    
    for (ll i = 0; i < n; i++) {
        cout << grundy(i) << ' ' << flush;
    }
    
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
