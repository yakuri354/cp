// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = 1e18; // sus

#ifdef DBG
#define inv(x)                                                       \
    if (!(x)) {                                                      \
        cerr << "invariant " #x " violated at " << __LINE__ << endl; \
        exit(-1);                                                    \
    }
#else
#define inv(x)
#endif

string s;
ll L, N, K;

ll ret(ll x, ll maxx) {
    if (x <= maxx) {
        return x;
    } else {
        return inf;
    }
}

ll dp(ll l, ll r, ll k, ll maxx) {
    if (k < 0) return inf;

    ll sz = r - l;
    if (sz == 1) {
        if (s[l] == '+' && k == 0) { // sus
            return inf;
        }

        if (k > 0) return ret(1, maxx);

        inv(s[l] >= '0' && s[l] <= '9');

        return ret(s[l] - '0', maxx);
    }

    if (sz == 2) { // mega sus
        ll left = s[l], right = s[l + 1];

        ll mink = (left == '+' || left == '0') + (right == '+');

        if (k < mink) return inf;

        if (k >= 1) {
            left = '1';
        }

        if (k >= 2) {
            right = '0';
        }

        return ret((left - '0') * 10 + (right - '0'), maxx);
    }

    ll ans = inf, pluses = 0;
    for (ll m = l + 1; m < r - 1; m++) {
        ll kp = s[m] != '+';

        pluses += s[m] == '+';
        
        for (ll k0 = 0; k0 <= k - kp; k0++) {
            ans = min(ans, dp(l, m, k0, maxx) + dp(m + 1, r, k - k0 - kp, maxx));
        }
    }

    if (r - l <= 10 && pluses == 0 && s[l] != '0' && s[l] != '+' && s[r-1] != '+') { // sus 
        try {
            ans = min(ans, ret(stoll(s.substr(l, r - l)), maxx));
        } catch (std::exception &e) { }
    }

    return ans;
}

void solve() {
    cin >> L >> N >> K >> s;

    ll lo = 0, hi = ll(1e18);
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        if (dp(0, s.size(), K, m) <= L) lo = m;
        else hi = m;
    }

    // todo
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
