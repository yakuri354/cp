// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cmath>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1ll << 50;

vector<ll> ps, psq, a;

vector<vector<fl>> d;
vector<vector<ll>> opt;

fl w(ll l, ll r) {
    fl sum = ps[r] - ps[l];
    fl mean = sum / fl(r - l);
    
    return (psq[r] - psq[l]) - 2 * mean * sum + (r - l) * mean * mean;
}

void dnc(ll ki, ll l, ll r, ll optl, ll optr) {
    ll m = (l + r) / 2;

    ll opt = optl;
    d[ki][m] = INFINITY;
    for (ll j = optl; j < min(optr, m); j++) {
        fl v = d[ki-1][j] + w(j, m);
        if (v < d[ki][m]) {
            opt = j;
            d[ki][m] = v;
        }
    }
    
    if (r - l <= 1) return;
    
    dnc(ki, l, m, optl, opt + 1);
    dnc(ki, m, r, opt, optr);
}

void solve() {
    ll n, k;
    cin >> n >> k;
    
    ps.resize(n + 1);
    psq.resize(n + 1);
    a.resize(n);

    for (ll &i: a) cin >> i;
    
    sort(a.begin(), a.end());
    
    for (ll i = 1; i <= n; i++) {
        ps[i] = ps[i-1] + a[i-1];
        psq[i] = psq[i-1] + a[i-1] * a[i-1];
    }
    
    d.assign(k + 1, vector<fl>(n + 1, INFINITY));
    
    d[0][0] = 0;

    opt.assign(k + 1, vector<ll>(n + 1));
    
    for (ll ki = 1; ki <= k; ki++) {
        dnc(ki, 1, n + 1, 0, n);
    }
    
    cout << fixed << setprecision(10) << d[k][n] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

