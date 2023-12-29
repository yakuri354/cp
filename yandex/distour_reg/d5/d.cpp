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

pair<ll, string> ret(ll x, string s, ll maxx) {
    if (x <= maxx) {
        return {x, s};
    } else {
        return {inf, ""};
    }
}

pair<ll, string> dp(ll l, ll r, ll k, ll maxx) {
    if (k < 0) return {inf, ""};

    ll sz = r - l;
    if (sz == 1) {
        if (s[l] == '+' && k == 0) { // sus
            return {inf, ""};
        }

        if (k > 0) return ret(1, "1", maxx);

        inv(s[l] >= '0' && s[l] <= '9');

        return ret(s[l] - '0', {s[l]}, maxx);
    }

    if (sz == 2) { // mega sus
        ll left = s[l], right = s[l + 1];

        ll mink = (left == '+' || left == '0') + (right == '+');

        if (k < mink) return {inf, ""};

        if (k >= 1) {
            left = '1';
        }

        if (k >= 2) {
            right = '0';
        }

        return ret((left - '0') * 10 + (right - '0'), s.substr(l, 2), maxx);
    }

    ll ans = inf, pluses = 0;
    string ans_str = "";
    for (ll m = l + 1; m < r - 1; m++) {
        ll kp = s[m] != '+';

        pluses += s[m] == '+';
        
        for (ll k0 = 0; k0 <= k - kp; k0++) {
            auto res1 = dp(l, m, k0, maxx), res2 = dp(m + 1, r, k - kp - k0, maxx);
            if (res1.first + res2.first < ans) {
                ans = res1.first + res2.first;
                ans_str = res1.second + '+' + res2.second;
            }
            // ans = min(ans, dp(l, m, k0, maxx) + dp(m + 1, r, k - k0 - kp, maxx));
        }
    }

    if (r - l <= 10 && pluses == 0 && s[l] != '0' && s[l] != '+' && s[r-1] != '+') { // sus 
        ll val = inf;
        try {
            val = stoll(s.substr(l, r - l));
        } catch (std::exception &e) { }

        if (val <= maxx && val <= ans && val != inf) {
            ans_str = s.substr(l, r - l);
            ans = val;
        }
    }

    return {ans, ans_str};
}

void solve() {
    cin >> L >> N >> K >> s;

    ll lo = 0, hi = N + 1;
    while (hi - lo > 1) {
        ll m = (lo + hi) / 2;

        auto res = dp(0, s.size(), K, m);
        // cerr << "at " << m << " = " << res.first << endl;
        if (res.first <= N) hi = m;
        else lo = m;
    }

    auto res = dp(0, s.size(), K, hi);
    if (res.first > N) {
        cout << -1 << endl;
        return;
    }
    cout << res.second << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

// 12+34 -> 1+1+4