// #pragma GCC optimize("Ofast")
#include <ios>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using fl = long double;

const ll maxn = 1e5 + 1;
const ull P = 307;

const ll k = 320;

ull p[maxn], h[maxn];

// ifstream fin("test1");

ull hs(ll l, ll r) {
    ull v = 0;
    if (r > 0) v += h[r-1];
    if (l > 0) v -= h[l-1];

    return v * p[l];
}

struct qr {
    ll l, r, i;
};

void solve() {
    string t;
    cin >> t;
    ll n = t.size();

    p[0] = 1;
    for (ll i = 1; i < n; i++) {
        p[i] = p[i-1] * P;
    }

    h[0] = t[0] * p[n - 1];
    for (ll i = 1; i < n; i++) {
        h[i] = h[i-1] + t[i] * p[n - i - 1];
    }

    ll m;
    cin >> m;

    vector<set<ull>> q_hashes(n);
    // q_hashes.max_load_factor(0.25);
    // q_hashes.reserve(m);
    set<ll> q_sizes;
    // q_hashes.max_load_factor(0.25);
    // q_hashes.reserve(sqrt(m) + 1);

    for (ll i = 0; i < m; i++) {
        string s;
        cin >> s;

        if (s.size() > n) continue;

        ull hq = s[0] * p[n - 1];
        for (ll i = 1; i < s.size(); i++) {
            hq += s[i] * p[n - i - 1];
        }
        q_hashes[s.size()].insert(hq);
        q_sizes.insert(s.size());
    }
    
    vector<map<ll, ll>> delta_r(n), delta_l(n);
    
    for (ll i = 0; i < n; i++) {
        for (ll j : q_sizes) {
            if (i + j > n) break;
            ull hh = hs(i, i + j);
            if (q_hashes[j].count(hh)) {
                delta_l[i][j]++;
                delta_r[i + j - 1][j]++;
            }
        }
    }
    
    ll q;
    cin >> q;

    vector<ll> q_ans(q);
    vector<qr> qs(q);

    for (ll i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--, qs[i].r--;
        qs[i].i = i;
    }
    
    sort(qs.begin(), qs.end(), [](qr l, qr r) {
        if (l.l / k == r.l / k) {
            if ((l.l / k) % 2 == 0) return l.r < r.r;
            else return l.r > r.r;
        }
        return l.l / k < r.l / k;
    });
    
    ll l = 0, r = -1, s = 0;
    for (ll i = 0; i < q; i++) {
        ll sz = r - l + 1;
        qr qq = qs[i];
        
        while (r < qq.r) { // -> r
            r++;
            sz++;
            for (auto [str_s, cnt] : delta_r[r]) {
                if (sz >= str_s) s += cnt;
                else break;
            }
        }
        while (l < qq.l) { // l ->
            for (auto [str_s, cnt] : delta_l[l]) {
                if (sz >= str_s) s -= cnt;
                else break;
            }
            l++;
            sz--;
        }
        while (qq.l < l) { // <- l
            l--;
            sz++;
            for (auto [str_s, cnt] : delta_l[l]) {
                if (sz >= str_s) s += cnt;
                else break;
            }
        }
        while (qq.r < r) { // r <-
            for (auto [str_s, cnt] : delta_l[l]) {
                if (sz >= str_s) s -= cnt;
                else break;
            }
            sz--;
            r--;
        }
        
        q_ans[qq.i] = s;
    }
    
    for (ll i = 0; i < q; i++) {
        cout << q_ans[i] << ' ';
    }
    
    cout << endl;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}
