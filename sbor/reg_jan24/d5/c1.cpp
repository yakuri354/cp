// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <string>
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

const ll maxh = 50 + 1;
const ll maxk = (1 << 5) + 1;

ll d[maxh][maxk];

ll revs(ll m, ll s) {
    ll res = 0;
    for (ll i = 0; i < s; i++) {
        res |= ((m >> (s - 1 - i)) & 1) << i;
    }
    return res;
}

void solve() {
    ll n;
    string s;

    cin >> s >> n;

    ll pwr = s.size();

    ll sn1 = 0, sn2 = 0;
    for (ll i = 0; i < s.size(); i++) {
        sn1 += (s[s.size() - i - 1] == 'b') * (1 << i);
        sn2 += (s[i] == 'b') * (1 << i);
    }

    ll h = n / 2;

    if (n <= 11) {
        ll ans = 0;

        // todo
    }

    for (ll m = 0; m < (1 << pwr); m++) {
        if (m == sn1 || m == sn2) continue;
        d[s.size()][m] = 1;
    }

    for (ll i = s.size() + 1; i <= h; i++) {
        for (ll m = 0; m < (1 << pwr); m++) {
            if (m == sn1 || m == sn2) {
                d[i][m] = 0;
            } else {
                ll prev = (m >> 1);
                d[i][m] = d[i-1][prev] + d[i-1][prev | (1 << (pwr - 1))];
            }
        }
    }

    ll ans = 0;
    for (ll m = 0; m < (1 << pwr); m++) {
        ans += d[h][m];
    }

    if (n % 2 == 0) {
        for (ll m1 = 0; m1 < (1 << pwr); m1++) {
            ll m2 = revs(m1, pwr);

            for 
        }
    }

    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

