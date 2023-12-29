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

pair<vector<ll>, vector<ll>> skuf_fast(string &s) {
    const ll n = s.size();
    vector<ll> p(n), c(n), cnt(max(256ll, n), 0);
    for (ll i = 0; i < n; i++)
        cnt[s[i]]++;
    for (ll i = 1; i < 256; i++)
        cnt[i] += cnt[i-1];
    for (ll i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    ll classes = 1;
    for (ll i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<ll> pn(n), cn(n);
    for (ll h = 0; (1 << h) < n; ++h) {
        for (ll i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (ll i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (ll i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (ll i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (ll i = 1; i < n; i++) {
            pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<ll, ll> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return {p, c};
}

vector<ll> calc_lcp(string &s, vector<ll> &pos, vector<ll> &cls) {
    const ll n = s.size();
    vector<ll> lcp(n);
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        if (cls[i] == n - 1) {
            curr = 0;
            continue;
        }
        
        ll nxt = pos[cls[i] + 1];

        while (max(nxt, i) + curr < n && s[i + curr] == s[nxt + curr]) curr++;

        lcp[cls[i]] = curr;
        curr = max(0ll, curr - 1);
    }

    return lcp;
}

struct sparse {
    ll lg = 21, n;
    vector<ll> tbl;

    sparse(vector<ll> v): n(v.size()), tbl(n * lg) {
        for (ll i = 0; i < n; i++) {
            tbl[i] = v[i];
        }

        for (ll l = 1; l < lg; l++) {
            for (ll i = 0; i + (1 << l) < n; i++) {
                tbl[n * l + i] = min(tbl[n * (l - 1) + i], tbl[n * (l - 1) + i + (1 << (l - 1))]);
            }
        }
    }

    ll rmq(ll l, ll r) {
        for (ll k = lg - 1; k >= 0; k--) {
            if (l + (1 << k) <= r) {
                return min(tbl[k * n + l], tbl[k * n + r - (1 << k)]);
            }
        }

        exit(-1);
    }
};

void dbg(string &t, vector<ll> &cls) {
    vector<pair<ll, string>> ss;

    for (ll i = 0; i < t.size(); i++) {
        ss.push_back({cls[i], t.substr(i)});
    }

    sort(ss.begin(), ss.end());

    for (auto [cl, s]: ss) {
        cout << s << endl;
    }

    cout << endl;

    sort(ss.begin(), ss.end(), [](auto a, auto b) {
        return a.second < b.second;
    });

    for (auto [cl, s]: ss) {
        cout << s << endl;
    }
}

void solve() {
    string t;
    cin >> t;

    const ll init_m = t.size();

    ll n;
    cin >> n;

    vector<pair<ll, ll>> subs;
    
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        t.push_back('+');
        subs.push_back({t.size(), s.size()});
        t += s;
    }

    t.push_back('#');

    auto [pos, cls] = skuf_fast(t);   
    auto lcp = calc_lcp(t, pos, cls);
    sparse st(lcp);

    vector<ll> ok_cls;
    for (ll i = 0; i < t.size(); i++) {
        if (pos[i] < init_m) {
            ok_cls.push_back(i);
        }
    }

    vector<ll> indices, ans_cnt(n);
    ll si = 0;
    for (auto [i, sz]: subs) {
        ll nxt = lower_bound(ok_cls.begin(), ok_cls.end(), cls[i]) - ok_cls.begin();

        while (st.rmq(cls[i], ok_cls[nxt]) >= sz) {
            indices.push_back(pos[ok_cls[nxt]]);
            ans_cnt[si]++;
        }

        si++;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ll t; cin >> t; while (t --> 0)
    solve();
}

