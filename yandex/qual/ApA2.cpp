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
const ll maxn = 40000;

ll a[maxn], b[maxn], da[maxn], db[maxn];

vector<ll> ga[maxn], gb[maxn];

void solve() {
    ll n, m, p;
    cin >> n >> m >> p;
    
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        da[i] = a[i];
    }

    for (ll i = 0; i < m; i++) {
        cin >> b[i];
        db[i] = b[i];
    }
    
    for (ll i = 0; i < p; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        ga[u].push_back(v);
        gb[v].push_back(u);
    }
    
    for (ll i = 0; i < n; i++) sort(ga[i].begin(), ga[i].end());
    for (ll i = 0; i < m; i++) sort(gb[i].begin(), gb[i].end());
    
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll mxv = a[i];
        for (ll j : ga[i]) {
            ll curr = mxv;
            mxv = max(mxv, db[j] + a[i]);
            db[j] = max(db[j], curr + b[j]);
        }
        ans = max(ans, mxv);
    }

    for (ll i = 0; i < m; i++) {
        ll mxv = b[i];
        for (ll j : gb[i]) {
            ll curr = mxv;
            mxv = max(mxv, da[j] + b[i]);
            da[j] = max(da[j], curr + a[j]);
        }        
        ans = max(ans, mxv);
    }
    
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
