#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <random>
 
using namespace std;
using ll = long long;
using li = __int128;
using ull = unsigned long long;
using fl = long double;
using pll = pair<ll, ll>;

void print(__int128 x) {
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    if (x > 9) print(x / 10);
    cout << char(x % 10 + '0');
}

void solve() {
    ll n;
    cin >> n;
 
    vector<ll> a(n), w(n);
    for (ll &i: a) cin >> i;
    for (ll &i: w) cin >> i;
 
    n++;
 
    // vector<ll> p(n), pinv(n);
    // iota(p.begin(), p.end(), 0);
 
    vector<ll> dp(1 << n, -1);
    vector<ll> par(1 << n, 0);
    vector<li> comb(1 << n, 0);
    dp[1] = 0;
    par[1] = 0;
    comb[1] = 1;
 
    for (ll _m = 0; _m < (1 << (n - 1)); _m++) {
        ll m = (_m << 1) | 1;
        if (dp[m] == -1) continue;
        for (ll i = 1; i < n; i++) {
            if (((m >> i) & 1) == 0 && ((m >> a[i - 1]) & 1) == 1) { // add from parent
                ll m2 = m ^ (1 << i);
                ll rel = dp[m] + __builtin_popcountll(m) * w[i-1];
                if (dp[m2] < rel) {
                    dp[m2] = rel;
                    par[m2] = i;
                    comb[m2] = comb[m];
                } else if (dp[m2] == rel) {
                    comb[m2] += comb[m];
                }
            }
        }
    }
 
    cout << dp[(1 << n) - 1] << endl;

    vector<ll> ans;
    ll last = (1 << n) - 1;
    while (last != 0 && par[last] != 0) {
        // cerr << par[last] << ' ';
        ans.push_back(par[last]);
        last ^= 1 << par[last];
    }

    reverse(ans.begin(), ans.end());

    for (ll i: ans) cout << setw(2) <<  i << ' ';
    cout << endl;

    for (ll i: ans) cout << setw(2) << (i == 0 ? 0 : w[i-1]) << ' ';

    cout << endl;

    print(comb[(1 << n) - 1]);

    cout << endl;
}
 
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}