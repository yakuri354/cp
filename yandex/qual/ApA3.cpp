// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll M = 998244353;

ll mod(ll x) {
    return (x % M + M) % M;
}

struct segt {
private:
    ll N;
    vector<ll> t, f, s;

    void upd(ll n) {
        s[n] = mod(s[n * 2 + 1] + s[n * 2 + 2]);
        t[n] = mod(t[n * 2 + 1] + t[n * 2 + 2]);
    }

    void push(ll n, ll nl, ll nr) {
        if (f[n] == 1) return;

        t[n] = mod(s[n] * f[n]);

        if (nr - nl > 1) {
            f[n * 2 + 1] = f[n];
            f[n * 2 + 2] = f[n];
            f[n] = 1;
        }
    }

    void set_factor(ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
        push(n, nl, nr);

        if (ql <= nl && nr <= qr) {
            f[n] = v;
            push(n, nl, nr);
            return;
        }

        if (qr <= nl || nr <= ql) {
            return;
        }

        ll m = (nl + nr) / 2;

        set_factor(n * 2 + 1, nl, m, ql, qr, v);
        set_factor(n * 2 + 2, m, nr, ql, qr, v);

        upd(n);
    }

    ll sum(ll n, ll nl, ll nr, ll ql, ll qr) {
        push(n, nl, nr);

        if (ql <= nl && nr <= qr) {
            return t[n];
        }

        if (qr <= nl || nr <= ql) {
            return 0;
        }

        ll m = (nl + nr) / 2;

        return mod(sum(n * 2 + 1, nl, m, ql, qr) +
                   sum(n * 2 + 2, m, nr, ql, qr));
    }

    void set(ll n, ll nl, ll nr, ll i, ll v) {
        push(n, nl, nr);

        if (nr - nl <= 1) {
            // cerr << "setting to " << nl << " as " << i << endl;
            s[n] = v;
            t[n] = mod(f[n] * s[n]);
            return;
        }

        ll m = (nl + nr) / 2;

        if (i < m) {
            set(n * 2 + 1, nl, m, i, v);
        } else {
            set(n * 2 + 2, m, nr, i, v);
        }

        upd(n);
    }
public:
    segt(ll n) : N(n), t(n * 4, 0), f(n * 4, 1), s(n * 4, 0) {
    }
    
    void set(ll i, ll v) {
        // cout << "set " << i << " = " << v << endl;
        set(0, 0, N, i, v);        
    }

    void set_factor(ll l, ll r, ll x) {
        // cout << "set_fac from " << l << " to " << r - 1 << " *= " << x << endl;
        set_factor(0, 0, N, l, r, x);
    }

    ll sum(ll l, ll r) {
        ll ans = sum(0, 0, N, l, r);
        // cout << "sum from " << l << " to " << r - 1 << " = " << ans << endl;
        return ans;
    }
};

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n), dp(n);

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll pm = a[0], pmx = a[0];

    vector<ll> maxpos{0}, minpos{0};
    segt maxt(n + 1), mint(n + 1);
    
    vector<ll> min_left(n), max_left(n), pref_min(n), pref_max(n);

    for (ll i = 1; i < n; i++) {
        pm = min(pm, a[i]);
        pmx = max(pmx, a[i]);
        pref_min[i] = pm;
        pref_max[i] = pmx;
    }
    
    for (ll i = 1; i < n; i++) {
        while (!maxpos.empty() && a[maxpos.back()] < a[i]) {
            maxpos.pop_back();
        }
        while (!minpos.empty() && a[minpos.back()] > a[i]) {
            minpos.pop_back();
        }

        min_left[i] = minpos.empty() ? 0 : (minpos.back() + 1);
        max_left[i] = maxpos.empty() ? 0 : (maxpos.back() + 1);

        maxpos.push_back(i);
        minpos.push_back(i);
    }

    for (ll i = 1; i < n; i++) {
        mint.set_factor(min_left[i], i + 1, a[i]);
        maxt.set_factor(max_left[i], i + 1, a[i]);
        
        ll max_sum = maxt.sum(1, i + 1);
        ll min_sum = mint.sum(1, i + 1);

        dp[i] = mod(pref_max[i] - pref_min[i] + max_sum - min_sum);

        mint.set(i + 1, dp[i]);
        maxt.set(i + 1, dp[i]);
    }
    
    cout << dp[n-1] << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
