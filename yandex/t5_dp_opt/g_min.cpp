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

vector<vector<ll>> d;
vector<ll> a;

struct counter {
    ll n, full = 0, ans = 0;
    
    vector<ll> cnt;
    
    ll l = 0, r = -1;
    
    counter(ll n): n(n), cnt(n, 0) {}
    
    void add(ll x) {
        ans += cnt[x];
        cnt[x]++;
    }
    
    void rm(ll x) {
        cnt[x]--;
        ans -= cnt[x];
    }
    
    void extend(ll l1, ll r1) {
        while (l1 < l) add(a[--l]);
        while (r1 > r) add(a[++r]);
        
        while (l < l1) rm(a[l++]);
        while (r > r1) rm(a[r--]);
    }
};

ll n, k;

void dnc(ll ki, ll l, ll r, ll optl, ll optr, counter &c) {
    ll m = (l + r) / 2;
    
    c.extend(optl, m - 1);
    
    ll opt = optl;
    d[ki][m] = inf;
    for (ll j = optl; j < min(m, optr); j++) {
        ll v = d[ki - 1][j] + c.ans;

        if (v < d[ki][m]) {
            d[ki][m] = v;
            opt = j;
        }
        
        c.rm(a[j]);
        c.l++;
    }
    
    if (r - l <= 1) return;
    
    dnc(ki, l, m, optl, opt + 1, c);
    dnc(ki, m, r, opt, optr, c);
}

void solve() {
    cin >> n >> k;
    
    a.resize(n);

    for (ll &i: a) cin >> i;
    
    d.assign(k + 1, vector<ll>(n + 1, inf));
    
    d[0][0] = 0;
    
    counter c(n + 1);
    for (ll i = 1; i <= k; i++) {
        dnc(i, 1, n + 1, 0, n + 1, c);
    }
    
    cout << d[k][n] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

