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

// def ord64(c):
//     x = ord(c)

//     if x >= 97:
//         return x - 97 + 38

//     if x >= 65:
//         return x - 65 + 12

//     if x >= 48:
//         return x - 48 + 2

//     if x >= 35:
//         return x - 35

//     if x in [35, 36]:
//         return x - 35
    
//     exit(-1)

vector<int> prefix_function(string &s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0)
            cur = p[cur - 1];
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}

ll find_s(string &t, string &s) {
    string tt = s + "_" + t + t;
    auto pf = prefix_function(tt);

    auto m = max_element(pf.begin() + s.size() + 1, pf.end());

    if (*m == s.size()) return m - pf.begin() - 2 * s.size();
    else return -1;
}

ll ord64(char c) {
    if (c >= 97) return c - 97 + 38;
    if (c >= 65) return c - 65 + 12;
    if (c >= 48) return c - 48 + 2;
    if (c >= 35) return c - 35;

    exit(-1);
}

// def unb64(s):
//     ans = 0
//     for i in range(len(s)):
//         ans += ord64(s[i]) * int(64 ** (len(s) - i - 1))
//     return ans

// def bn(x, l):
//     return "".join(['1' if (x & (1 << i)) > 0 else '0' for i in range(l)])

// ll find_hash(string &t, string &s) {
//     vector<ull> hs(t.size() * 2);
// }

void solve() {
    ll k, m;
    cin >> k >> m;

    for (ll i = 0; i < m; i++) {
        string s0, s1;
        cin >> s0 >> s1;

        string b0, b1;

        for (ll j = 0; j < k; j++) {
            ll x = ord64(s0[j]);
            for (ll y = 5; y >= 0; y--) {
                b0.push_back('0' + ((x >> y) & 1));
            }
        }

        for (ll j = 0; j < k; j++) {
            ll x = ord64(s1[j]);
            for (ll y = 5; y >= 0; y--) {
                b1.push_back('0' + ((x >> y) & 1));
            }
        }
        
        auto b2 = b0 + b0;

        cout << find_s(b2, b1) << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

