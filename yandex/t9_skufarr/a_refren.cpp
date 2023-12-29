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

pair<vector<ll>, vector<ll>> skuf(vector<ll> &s) {
    ll n = s.size();

    vector<ll> cls(n);
    for (ll i = 0; i < n; i++) {
        cls[i] = s[i];
    }

    for (ll l = 1; l < n * 2; l *= 2) {
        vector<pair<ll, ll>> z;
        for (ll i = 0; i < n; i++) {
            z.push_back({cls[i] * 1000000000ll + cls[(i + l) % n], i});
        }

        sort(z.begin(), z.end());

        ll c = 0;
        cls[z[0].second] = 0;
        for (ll i = 1; i < n; i++) {
            if (z[i].first != z[i - 1].first) {
                c++;
            }
            cls[z[i].second] = c;
        }
    }

    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        p[cls[i]] = i;
    }

    return {p, cls};
}

vector<ll> calc_lcp(vector<ll> &p, vector<ll> &cls, vector<ll> &s) {
    const ll n = s.size();
    ll curr = 0;
    vector<ll> lcp(n);
    for (ll i = 0; i < n; i++) {
        if (cls[i] == n - 1) {
            curr = 0;
            continue;
        }

        ll nxt = p[cls[i] + 1];

        while (i + curr < n && nxt + curr < n && s[i + curr] == s[nxt + curr]) curr++;

        lcp[cls[i]] = curr;
        curr = max(0ll, curr - 1);
    }

    return lcp;
}

const ll logn = 19;
const ll maxn = 150000;

ll st[logn][maxn];

void st_init(vector<ll> &a) {
    const ll n = a.size();

    for (ll i = 0; i < n; i++) {
        st[0][i] = a[i];
    }

    for (ll lg = 1; lg < logn; lg++) {
        for (ll i = 0; i + (1 << lg) <= n; i++) {
            st[lg][i] = min(st[lg - 1][i], st[lg - 1][i + (1 << (lg - 1))]);
        }
    }
}

ll lg2(ll x) {
    if (x == 0) return -1;
    return __builtin_clzll(1) - __builtin_clzll(x);
}

ll st_min(ll l, ll r) {
    ll z = lg2(r - l);
    return min(st[z][l], st[z][r - (1 << z)]);
}

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n);
    for (ll &i: a) cin >> i;

    a.push_back(-1);
    n++;

    auto [p, cls] = skuf(a);
    auto lcp = calc_lcp(p, cls, a);

    st_init(lcp);

    ll best_ans = -INT32_MAX, ans_l = -1, ans_r = -1;
    for (ll i = 0; i < n; i++) {
        ll lo_l = 0, hi_l = i;
        while (hi_l - lo_l > 1) {
            ll m = (hi_l + lo_l) / 2;

            if (st_min(m, i + 1) == lcp[i]) hi_l = m;
            else lo_l = m;
        }

        if (st_min(lo_l, i + 1) == lcp[i]) hi_l = lo_l;

        ll lo_r = i, hi_r = n;
        while (hi_r - lo_r > 1) {
            ll m = (hi_r + lo_r) / 2;

            if (st_min(i, m + 1) == lcp[i]) lo_r = m;
            else hi_r = m;
        }

        lo_r++; // lcp is [l, r)

        ll res = (lo_r - hi_l + 1) * lcp[i];
        if (res > best_ans) {
            ans_l = p[i];
            ans_r = p[i] + lcp[i] - 1;
            best_ans = res;
        }
    }

    if (best_ans < n - 1) {
        best_ans = n - 1;
        ans_l = 0;
        ans_r = n - 2;
    }

    cout << best_ans << '\n';
    cout << ans_r - ans_l + 1 << '\n';
    for (ll i = ans_l; i <= ans_r; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

