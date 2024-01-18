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
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxa = 100;

void solve() {
    ll n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        cout << 0 << endl;
        return;
    }

    vector<ll> d2;

    ll curr = n;
    for (ll i = 2; i * i <= n; i++) {
        if (curr % i == 0) {
            d2.push_back(i);
            if (i != n / i) d2.push_back(n / i);
        }
    }

    d2.push_back(n);

    sort(d2.begin(), d2.end());

    unordered_map<ll, ll> di;
    for (ll i = 0; i < d2.size(); i++) {
        di[d2[i]] = i;
    }

    const ll D = d2.size();

    vector<set<ll>> dp(D, set<ll>());

    for (ll i = 0; i < D; i++) {
        dp[i].insert(d2[i] - 1);
    }

    for (ll i = 0; i < D; i++) {
        for (ll j = 0; j < i; j++) {
            if (d2[i] % d2[j] == 0) {
                ll ri = di[d2[i]/d2[j]];
                for (ll x: dp[ri]) {
                    dp[i].insert(x + d2[j] - 1);
                }
            }
        }
    }

    cout << dp[di[n]].size() << '\n';
    for (ll x: dp[di[n]]) {
        cout << x << ' ';
    }
    cout << endl;

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

