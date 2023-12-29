#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cmath>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <random>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <functional>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const ll INF = 2e9;
const ll MAXN = 2e5 + 5;
const ll MOD = 1e9 + 7;
const ll logn = 18;
const ll k = 31;

ll p[MAXN];

vector<ll> h;
ll hs(ll l, ll r) {
    return ((h[r] - h[l - 1] * p[r - l + 1]) % MOD + MOD) % MOD;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    string s;
    cin >> s;
    h.assign(m + 1, 1);
    p[0] = 1;
    for (ll i = 1; i <= m; ++i) {
        h[i] = (h[i - 1] * k + (s[i - 1] - 'a')) % MOD;
        p[i] = (p[i - 1] * k) % MOD;
    }

    vector<ll> a(n);
    vector<string> strs(n);
    for (ll i = 0; i < n; ++i) {
        string t;
        cin >> t;
        strs[i] = t;

        for (int j = 0; j < (int)t.size(); ++j) {
            a[i] *= k;
            a[i] += (t[j] - 'a');
        }
    }

    vector<vector<int>> occ(n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i + (ll)strs[j].size() > m) {
                continue;
            }
            if (hs(i + 1, i + (ll)strs[j].size()) == a[j]) {
                occ[j].push_back(i);
            }
        }
    }

    vector<ll> tmp(n);
    iota(tmp.begin(), tmp.end(), 0);

    ll ans = m;
    do {
        auto lol = tmp.begin();
        ll it = 0;
        for (int i = 0; i < n; ++i) {
            auto kek = lower_bound(occ[*lol].begin(), occ[*lol].end(), it);
            if (kek == occ[*lol].end()) {
                break;
            }

            it = *kek + (int)strs[*lol].size();
            if (i == n - 1) {
                ans = min(ans, it);
            }
            ++lol;
        }
    } while (next_permutation(tmp.begin(), tmp.end()));

    if (ans == m) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef APPLE
    freopen("in", "r", stdin);
#endif

    ll T = 1;
    //cin >> T;
    while (T --> 0) {
        solve();
    }

    return 0;
}