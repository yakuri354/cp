#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll inf = INT32_MAX;
const ll maxn = 3e5;

template<typename Monoid>
struct segt {
private:
    ll NONE = -inf;
    
    Monoid z;

    ll N;
    vector<ll> t, f;
    
    void upd(ll n) {
        t[n] = z.op(t[n * 2 + 1], t[n * 2 + 2]);
    }
    
    void build(ll n, ll nl, ll nr, const vector<ll> &s) {
        if (nr - nl <= 1) {
            t[n] = s[nl];
            return;
        }
        
        ll m = (nl + nr) / 2;
        
        build(n * 2 + 1, nl, m, s);
        build(n * 2 + 2, m, nr, s);
        
        upd(n);
    }

    void push(ll n, ll nl, ll nr) {
        if (f[n] == NONE) return;
        
        t[n] = z.empty(f[n], nr - nl);

        if (nr - nl > 1) {
            f[n * 2 + 1] = f[n];
            f[n * 2 + 2] = f[n];
        }

        f[n] = NONE;
    }

    void mass_assign(ll n, ll nl, ll nr, ll ql, ll qr, ll v) {
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

        mass_assign(n * 2 + 1, nl, m, ql, qr, v);
        mass_assign(n * 2 + 2, m, nr, ql, qr, v);

        upd(n);
    }

    ll sum(ll n, ll nl, ll nr, ll ql, ll qr) {
        push(n, nl, nr);

        if (ql <= nl && nr <= qr) {
            return t[n];
        }

        if (qr <= nl || nr <= ql) {
            return z.e;
        }

        ll m = (nl + nr) / 2;

        return z.op(sum(n * 2 + 1, nl, m, ql, qr),
                   sum(n * 2 + 2, m, nr, ql, qr));
    }

    void set(ll n, ll nl, ll nr, ll i, ll v) {
        push(n, nl, nr);

        if (nr - nl <= 1) {
            t[n] = v; // SUS
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
    
    ll first_more_pref_sum(ll n, ll nl, ll nr, ll x) {
        push(n, nl, nr);

        if (nr - nl <= 1) {
            if (t[n] > x) {
                return nl;
            } else {
                return -1;
            }
        }

        ll m = (nl + nr) / 2;
        push(n * 2 + 1, nl, m);

        if (t[n * 2 + 1] > x) {
            return first_more_pref_sum(n * 2 + 1, nl, m, x);
        } else {
            return first_more_pref_sum(n * 2 + 2, m, nr, x - t[n * 2 + 1]);
        }
    }

    
    ll first_less_eq(ll n, ll nl, ll nr, ll x) {
        push(n, nl, nr);

        if (nr - nl <= 1) {
            if (t[n] <= x) {
                return nl;
            } else {
                return -1;
            }
        }

        ll m = (nl + nr) / 2;
        
        push(n * 2 + 1, nl, m);

        if (t[n * 2 + 1] <= x) {
            return first_less_eq(n * 2 + 1, nl, m, x);
        } else {
            return first_less_eq(n * 2 + 2, m, nr, x);
        }
    }
public:
    segt(ll n) : N(n), t(N * 4, 0), f(N * 4, NONE) {
    }

    segt(const vector<ll> &v) : N(v.size()), t(N * 4, 0), f(N * 4, NONE) {
        build(0, 0, N, v);
    }
    
    void set(ll i, ll v) {
        set(0, 0, N, i, v);        
    }

    void mass_assign(ll ql, ll qr, ll v) {
        mass_assign(0, 0, N, ql, qr, v);
    }

    ll sum(ll l, ll r) {
        ll ans = sum(0, 0, N, l, r);
        return ans;
    }

    ll first_more_pref_sum(ll x) {
        return first_more_pref_sum(0, 0, N, x);
    }

    ll first_less_eq(ll x) {
        return first_less_eq(0, 0, N, x);
    }
};

struct MSum {
    ll e = 0;

    ll op(ll a, ll b) {
        return a + b;
    }

    ll empty(ll v, ll cnt) {
        return v * cnt;
    }
};

struct MLess {
    ll e = inf;

    ll op(ll a, ll b) {
        return min(a, b);
    }

    ll empty(ll v, ll cnt) {
        return v;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n);
    
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    segt<MSum> sum_segt(a);
    segt<MLess> less_segt(a);

    for (ll i = 0; i < m; i++) {
        ll t, k, x;
        cin >> t >> k >> x;
        k--;

        if (t == 1) {
            ll first = less_segt.first_less_eq(x);
            if (first == -1 || first > k) continue;
            
            less_segt.mass_assign(first, k + 1, x);
            sum_segt.mass_assign(first, k + 1, x);
        } else {
            ll ans = 0;
            for (;;) {
                ll first = less_segt.first_less_eq(x);

                if (first == -1) break;

                if (first < k) first = k;

                ll end = sum_segt.first_more_pref_sum(sum_segt.sum(0, first) + x);

                if (end == -1) end = n;
                
                ans += end - first;
                x -= sum_segt.sum(first, end);

                k = end;
                if (k >= n) break;
            }
            
            cout << ans << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
