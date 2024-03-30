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
using pll = pair<ll, ll>;

vector<vector<ll>> a;

ll n, m;
ll calc(string &s) {
    ll i = 0, j = 0;
    ll res = a[0][0];
    for (char c: s) {
        if (c == 'R') {
            j++;
        }
        if (c == 'L') {
            j--;
        }
        if (c == 'D') {
            i++;
        }
        if (c == 'U') {
            i--;
        }

        if (i >= 0 && i < n && j >= 0 && j < m) res += a[i][j];
    }
    return res;
}

void solve() {
    cin >> n >> m;
    a.resize(n, vector<ll>(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    string s;
    cin >> s;

    ll z = s.size();

    ll val = 0;
    string ans = s;

    for (ll i = 0; i < z; i++) {
        auto x = s[i];
        s.erase(s.begin() + i);
        auto s2 = s;

        for (ll j = 0; j <= s2.size(); j++) { // sus
            s2.insert(s2.begin() + j, x);
            ll y = calc(s2);
            // cout << s2 << " -> " << y << endl;
            if (y < val) {
                ans = s2;
                val = y;
            }
            s2.erase(s2.begin() + j);
        }
        
        s.insert(s.begin() + i, x);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

