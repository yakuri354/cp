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
const ll maxn = 10000;
const ull P = 101;
const ull MOD = ~0ull;

ull mod(ull x) {
    return (x + (x % MOD)) % MOD;
}

ull p[maxn + 1];

ull ph(ll l, ll r, vector<ull> &h) {
    ull v = 0;
    if (r > 0)
        v += h[r - 1];
    if (l > 0)
        v = mod(v - h[l - 1]);

    return mod(v * p[l]);
}

vector<string> s;
vector<vector<ull>> hs;

ll k;

bool check(ll l) {
    if (l == 0) return true;
    set<ull> z;
    for (ll i = 0; i < k; i++) {
        set<ull> local;
        for (ll j = 0; j + l <= s[i].size(); j++) {
            local.insert(ph(j, j + l, hs[i]));
        }
        if (i == 0) {
            z = local;
        } else {
            for (auto it = z.begin(); it != z.end();) {
                if (!local.count(*it)) {
                    it = z.erase(it);
                } else {
                    it++;
                }
            }
        }
    }

    return z.size() > 0;
}

void solve() {
    p[0] = 1;
    for (ll i = 1; i <= maxn; i++) {
        p[i] = p[i-1] * P;
    }

    cin >> k;

    hs.resize(k);
    s.resize(k);

    for (string &x: s) cin >> x;

    ll min_sz = inf;
    for (ll i = 0; i < k; i++) {
        hs[i].resize(s[i].size());
        min_sz = min(min_sz, ll(s[i].size()));
        hs[i][0] = s[i][0] * p[maxn];
        for (ll j = 1; j < s[i].size(); j++) {
            hs[i][j] = hs[i][j-1] + s[i][j] * p[maxn - j];
        }
    }

    ll lo = 0, hi = min_sz + 1;
    while (hi - lo > 1) {
        ll m = (hi + lo) / 2;

        if (check(m)) lo = m;
        else hi = m;
    }

    if (lo == 0) {
        cout << endl;
        return;
    }

    unordered_set<ull> z;
    for (ll i = 0; i < k; i++) {
        unordered_set<ull> local;
        for (ll j = 0; j + lo <= s[i].size(); j++) {
            local.insert(ph(j, j + lo, hs[i]));
        }
        if (i == 0) {
            z = local;
        } else {
            for (auto it = z.begin(); it != z.end();) {
                if (!local.count(*it)) {
                    it = z.erase(it);
                } else {
                    it++;
                }
            }
        }
    }

    for (ll j = 0; j + lo <= s[0].size(); j++) {
        if (z.count(ph(j, j + lo, hs[0]))) {
            cout << s[0].substr(j, lo) << endl;
            return;
        }
    }

    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

